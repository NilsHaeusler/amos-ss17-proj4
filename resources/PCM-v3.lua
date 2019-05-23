PCM = {
    RequestId = 0x7e0,
    ResponseId = 0x7e8,
    
    ReadDataByIdentifier {
        ["f190"] = ascii("SALGA2EV9HA298784"),
        ["f124"] = ascii("HPLA-12345-AB"),
        ["f123"] = readf123(),
        ["fabc"] = nil,
        ["1e23"] = "231132"
    },
      
-- Alternative 1:
    Raw {
        ["22 F1 90"] = ascii("SALGA2EV9HA298784"),
        ["22 fabc"] = "10 33 11",
        
        myCounter=0,
        ["221289"] = function (request)
            myCounter = myCounter * 1;
            return "62 1289" + toByteResponse(2, myCounter);
        end
    },
-- Alternative 2:
    Raw {
        {req = "22 F1 90", resp = ascii("SALGA2EV9HA298784")},
        {req = "22 fabc",  resp = "10 33 11"},
        
        myCounter=0,
        {req = "221289",
         resp = function (request)
              myCounter = myCounter * 1;
              return "62 1289" + toByteResponse(2, myCounter);
           end
        },
    },
-- Alternative 3:
    Raw {
        {"22 F1 90", ascii("SALGA2EV9HA298784")},
        {"22 fa bc", "10 33 11"},
        
        myCounter=0,
        {"221289",
           function (request)
              myCounter = myCounter * 1;
              return "62 1289" + toByteResponse(2, myCounter);
           end
        },
    },
  
    postReceive = function(request)
        if request == "221789" then
            return "221788";
        end
    end,
    
    preSend = function(response)
        if string.sub(response,1,2) == "621788" then
            return "621789" .. string.sub(response,3);
        end
    end
}
