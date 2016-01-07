-- zergl <e3.gemini@qq.com>
-- 2016/01/07
--[[
configuration block in nginx.conf:
    lua_shared_dict hits_counter 1M;

    location /page_hits {
        default_type text/plain;
        lua_code_cache off;
        content_by_lua_file resty_apps/page_hits.lua;
    }
--]]

local hc = ngx.shared.hits_counter
local key = "_hits"

hits = hc:get(key)
hits = hits == nil and 1 or hits + 1
local succ, err, f = hc:set(key, hits)
--ngx.say("succ:", succ, " err:", err, " forcible:", f)
ngx.say("page_hits: ", hits)

