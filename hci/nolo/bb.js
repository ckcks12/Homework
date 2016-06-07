var Place = Backbone.Model.extend(
{
    defaults:
    {
        title: "",
        content: "",
        image_url: "",
        contentid: ""
    },
    initialize: function()
    {
        this.collection.on("reset", ()=>this.trigger("reset"));
    },
    parse: function(d)
    {
        if( this.image_url === undefined || this.image_url == "" )
        {
            d.image_url = d.firstimage !== undefined ? d.firstimage : "http://www.realestatemarketingdude.com/wp-content/uploads/2015/01/questionmark-300x200.png";
        }

        Backbone.ajax(
        {
            url: window.api.detailIntro(10, 1, d.contentid, d.contenttypeid, "Y"),
            success: (k) =>
            {
                k = k.response.body.items.item;
                _.extend(this.attributes, k);
                if( k.playtime !== undefined )
                {
                    this.set("content", k.playtime);
                }
            }
        });

        return d;
    }
});

var PlaceCol = Backbone.Collection.extend(
{
    model: Place,
    page_no: 1,
    url: function()
    {
        return window.api.areaBasedList(10, this.page_no++, "B", "Y");
    },
    parse: function(d)
    {
        if( d.response.body.items.item === undefined || d.response.body.items.item.length == 0 )
        {
            $("#SearchResult").html("<div class='ui center aligned'>검색 결과가 없습니다</div>");
            return;
        }
        return d.response.body.items.item;
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
        this.model.on('change', this.render, this);
        this.model.on("reset", ()=>this.remove());
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
        load();
    }
});






var place_col = new PlaceCol();
window.view_arr = [];

function load()
{
    place_col.fetch(
    {
        success: function()
        {
            place_col.each(function(m)
            {
                window.view_arr[window.view_arr.length] = new PlaceView({model: m});
            });
        }
    });
}