-- main.lua
-- @zergl, 2016/01/07
--

function echo(k,v)
    ngx.say(k, " : ", v, "<br>")
end
--[[
-- ngx.say('hello @todo.main')
ngx.say('uri: ', ngx.var.uri, '<br>')
ngx.say('uri: ', ngx.var.request_uri, '<br>')
ngx.say('schema: ', ngx.var.schema, "<br>")
echo("method", ngx.var.request_method)
echo("query_string", ngx.var.query_string)
echo("host", ngx.var.host)
echo("user_agent", ngx.var.http_user_agent)
echo("filename", ngx.var.request_filename)
echo("remote_addr", ngx.var.remote_addr)
echo("remote_port", ngx.var.remote_port)

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
--]]
local qs_args = ngx.req.get_uri_args()

local cmd = qs_args['cmd']

function do_add(args)
    for k,v in pairs(args) do
        ngx.say("add: ",k,"->", v, "<br>")
    end
    return true,"", "add succ."
    --return nil,"exists", "add fail."
end

function do_del()
    return false,"not exist.","result: del fail."
end

function do_update()
    return false, "not supported yet.", ""
end

ops = {
    ["add"]     = do_add,
    ["del"]     = do_del,
    ["update"]  = do_update
}

local succ, err, resp = false, "opcode not supported.", nil
local do_exec = ops[cmd]
if do_exec then
    succ, err, resp = do_exec(qs_args)
end

--todo: fail to get return values of 'err' and 'resp'!!!
--local succ, err, resp = do_exec and do_exec(qs_args) or false,"opcode not supported.",nil

-- debug info
echo("succ", succ)
echo("err ", err)
echo("resp", resp)
ngx.say('<input type=\"button\" value=\"click\" onclick=\"alert(\'you click me!!!\');\" />')
ngx.exit(ngx.HTTP_OK)

