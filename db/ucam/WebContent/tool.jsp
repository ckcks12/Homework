<%!
    String alertToBack(String s)
    {
        String str;
        str = "<script>alert('" + s + "');history.back();</script>";
        return str;
    }

    String alertToUrl(String s, String url)
    {
        String str;
        str = "<script>alert('" + s + "');location.href = '" + url + "';</script>";
        return str;
    }

    String toUrl(String url)
    {
        String str;
        str = "<script>location.href = '" + url + "';</script>";
        return str;
    }
%>