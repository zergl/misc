-- echo.lua
-- @zergl, 2016/01/07

function echo(k,v)
    ngx.say(k, " : ", v, "<br>")
end

local _M = {}

function _M.hello()
    ngx.say("hello from info.lua", "<br>")
    --return false, "hello from sub-module.", "popopo..."
    return true, "hello from sub-module.", "popopo..."
end

function _M.print_info()
    ngx.say("<title>print_info @ todo.io</title>")
    ngx.say("hello @todo.main", "<br>")
    echo("ngx.var.uri", ngx.var.uri)
    echo("ngx.var.request_uri", ngx.var.request_uri)
    echo("schema", ngx.var.schema)
    echo("method", ngx.var.request_method)
    echo("query_string", ngx.var.query_string)
    echo("host", ngx.var.host)
    echo("user_agent", ngx.var.http_user_agent)
    echo("filename", ngx.var.request_filename)
    echo("remote_addr", ngx.var.remote_addr)
    echo("remote_port", ngx.var.remote_port)
    ngx.say("-------------------")

    local html_content = "<h1>headers</h1>"
    ngx.say(html_content)
    local headers = ngx.req.get_headers()
    for k,v in pairs(headers) do
        echo(k,v)
    end

    ngx.say("<h1>uri_args</h1>")
    local uri_args = ngx.req.get_uri_args()
    for k,v in pairs(uri_args) do
        echo(k, v)
    end
end

return _M
