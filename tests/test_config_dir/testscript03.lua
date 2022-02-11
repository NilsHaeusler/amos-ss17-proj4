PCM = {
    RequestId = 0x100,
    ResponseId = 0x200,

    Seed = {
    	[0x01] = "0x4455",
    	[0x03] = "0x6677",
    },

    ReadDataByIdentifier = { -- "=" on tables is necessary
        [0xf190] = "SALGA2EV9HA298784",
        [0xf124] = "HPLA-12345-AB",
        [0xf123] = nil,
        [0xfabc] = nil,
        [0x1e23] = "231132",
    },

    Raw = {
        ["10 02"] = "50 02 00 19 01 f4",
        ["22 fa bc"] = "10 33 11",

        -- As an alternative, requests and responses can be specified
        -- using concatenation, functions or any other language
        -- features of lua
        ["22 F1 90"] = "62 F1 90" .. ascii("SALGA2EV9HA298784")
    }
}

