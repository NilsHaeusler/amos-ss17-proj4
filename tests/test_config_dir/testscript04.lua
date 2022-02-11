PCM = {
    RequestId = 0x101,
    ResponseId = 0x201,

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
    }
}


