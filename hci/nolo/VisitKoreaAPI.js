function getArgName(func) {
  // First match everything inside the function argument parens.
  var args = func.match(/function\s.*?\(([^)]*)\)/)[1];
 
  // Split the arguments string into an array comma delimited.
  return args.split(',').map(function(arg) {
    // Ensure no inline comments are parsed and trim the whitespace.
    return arg.replace(/\/\*.*\*\//, '').trim();
  }).filter(function(arg) {
    // Ensure no undefined values are added.
    return arg;
  });
}

var VisitKoreaAPI = function()
{
    this.createUrl = function(api_name, arg_name, arg_val)
    {
        //var url = "http://api.visitkorea.or.kr/openapi/service/rest/KorService/" + api_name + "?ServiceKey=tM%2BbwWQD383lWLKYsJUEFDxC2NoGAvT5rTymTZpfaknMV4FYXam%2FzA3TsqAp%2FkfPbM0tlV%2BaLsut%2B8TigqmgSg%3D%3D&MobileOS=ETC&MobileApp=Nolo&_type=json";
        var url = "http://api.visitkorea.or.kr/openapi/service/rest/KorService/" + api_name + "?ServiceKey=인증키&MobileOS=ETC&MobileApp=Nolo&_type=json";

        for( i=0; i<arg_name.length; i++ )
        {
            var name = arg_name[i];
            var val;
            if( i < arg_val.length )
            {
                val = arg_val[i];
            }
            else
            {
                val = "";
            }

            url += "&" + name + "=" + encodeURI(val);
        }

        return url;
    };

    this.areaCode = function areaCode(numOfRows, pageNo, areaCode, signguCode)
    {
        return this.createUrl(arguments.callee.name, getArgName(arguments.callee.toString()), arguments);
    };

    this.categoryCode = function categoryCode(numOfRows, pageNo, contentTypeId, cat1, cat2, cat3)
    {
        return this.createUrl(arguments.callee.name, getArgName(arguments.callee.toString()), arguments);
    }

    this.areaBasedList = function areaBasedList(numOfRows, pageNo, arrange, listYN, contentTypeId, areaCode, signguCode, cat1, cat2, cat3)
    {
        return this.createUrl(arguments.callee.name, getArgName(arguments.callee.toString()), arguments);
    }

    this.locationBasedList = function locationBasedList(numOfRows, pageNo, arrange, listYN, contentTypeId, mapX, mapY, radius)
    {
        return this.createUrl(arguments.callee.name, getArgName(arguments.callee.toString()), arguments);
    }

    this.searchKeyword = function searchKeyword(numOfRows, pageNo, arrange, listYN, contentTypeId, keyword, areaCode, signguCode, cat1, cat2, cat3)
    {
        return this.createUrl(arguments.callee.name, getArgName(arguments.callee.toString()), arguments);
    }

    this.searchFestival = function searchFestival(numOfRows, pageNo, arrange, listYN, eventStartDate, eventEndDate, areaCode, signguCode)
    {
        return this.createUrl(arguments.callee.name, getArgName(arguments.callee.toString()), arguments);
    }

    this.searchStay = function searchStay(numOfRows, pageNo, arrange, listYN, contentTypeId, hanOk, benikia, goodStay, areaCode, signguCode)
    {
        return this.createUrl(arguments.callee.name, getArgName(arguments.callee.toString()), arguments);
    }

    this.detailCommon = function detailCommon(numOfRows, pageNo, contentId, contentTypeId, defaultYN, firstImageYN, areacodeYN, catcodeYN, addrinfoYN, mapinfoYN, overviewYN)
    {
        return this.createUrl(arguments.callee.name, getArgName(arguments.callee.toString()), arguments);
    }

    this.detailIntro = function detailIntro(numOfRows, pageNo, contentId, contentTypeId, introYN)
    {
        return this.createUrl(arguments.callee.name, getArgName(arguments.callee.toString()), arguments);
    }

    this.detailInfo = function detailInfo(numOfRows, pageNo, contentId, contentTypeId, detailYN)
    {
        return this.createUrl(arguments.callee.name, getArgName(arguments.callee.toString()), arguments);
    }

    this.detailImage = function detailImage(numOfRows, pageNo, contentId, contentTypeId, imageYN)
    {
        return this.createUrl(arguments.callee.name, getArgName(arguments.callee.toString()), arguments);
    }
}
window.api = new VisitKoreaAPI();