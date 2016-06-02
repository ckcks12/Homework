var Place = Backbone.Model.extend(
{
    defaults:
    {
        title: "t-",
        content: "-",
        image_url: ""
    },
    parse: function(d)
    {
        var tmp = {};
        tmp.title = d.title;
        tmp.content = "aa";
        tmp.image_url = d.firstimage !== undefined ? d.firstimage : "http://www.realestatemarketingdude.com/wp-content/uploads/2015/01/questionmark-300x200.png";

        return tmp;
    }
});

var PlaceCol = Backbone.Collection.extend(
{
    model: Place,
    url: function()
    {
        this.page_no++;
        return "http://api.visitkorea.or.kr/openapi/service/rest/KorService/areaBasedList" 
                + "?ServiceKey=tM%2BbwWQD383lWLKYsJUEFDxC2NoGAvT5rTymTZpfaknMV4FYXam%2FzA3TsqAp%2FkfPbM0tlV%2BaLsut%2B8TigqmgSg%3D%3D"
                + "&MobileOS=ETC&MobileApp=Nolo&_type=json"
                + "&numOfRows=" + this.num_of_row
                + "&pageNo=" + this.page_no
                + "&arrange=" + this.arrange
                + "&listYN=" + this.list_yn
                + "&contentTypeId=" + this.content_type_id
                + "&areaCode=" + this.area_code
                + "&signguCode=" + this.signgu_code
                + "&cat1=" + this.cat1
                + "&cat2=" + this.cat2
                + "&cat3=" + this.cat3;
    },
    num_of_row: 10,
    page_no: 0,
    arrange: "B",
    list_yn: "Y",
    content_type_id: "",
    area_code: "",
    signgu_code: "",
    cat1: "",
    cat2: "",
    cat3: "",
    parse: function(d)
    {
        return d.response.body.items.item;
        //console.log(d);
    }
});
    
var PlaceView = Backbone.View.extend(
{
    tpl: _.template(document.getElementById("PlaceView").innerText),
    el: function()
    {
        return $("#SearchResult").append("<div></div>").children().last();
    },
    initialize: function()
    {
        //this.el = $("#SearchResult").append("<div></div>").children().last();
        this.model.on('change', this.render, this);
        this.render();
    },
    events:
    {
        "click": "mousemove"
    },
    render: function()
    {
        this.el.innerHTML = this.tpl(this.model.toJSON());
        return this;
    },
    mousemove: function()
    {
        this.model.collection.page_no++;
        load();
    }
});







var place = new Place;
var place2 = new Place;
var place_col = new PlaceCol();
//var place_view = new PlaceView({model: place});
//var place_view2 = new PlaceView({model: place2});
window.view_arr = [];
load();
function load()
{
    place_col.fetch(
    {
        reset: true,
        success: function()
        {
            place_col.each(function(m)
            {
                console.log(m);
                window.view_arr[window.view_arr.length] = new PlaceView({model: m});
            });
        }
    });
}