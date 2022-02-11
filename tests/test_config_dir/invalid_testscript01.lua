-- This file only contains broken ECU configurations for the sake of unit testing.
-- Do not consider this file as working examples!

TC01 = { -- first test case
    -- no request ID
    -- RequestId = 0x100,
    ResponseId = 0x200,
    BroadcastId = 0x300,

    ReadDataByIdentifier = {
        ["F1 90"] = "SALGA2EV9HA298784",
        ["F1 24"] = "HPLA-12345-AB",
        ["1E 23"] = "231132",
    },

    Raw = {
        ["10 02"] = "50 02 00 19 01 f4",
        ["22 fa bc"] = "10 33 11",
        ["22 F1 91"] = "62 F1 91" .. ascii("SALGA2EV9HA298784")
    }
}

TC02 = { -- second test case
    -- no respond ID
    RequestId = 0x100,
    -- ResponseId = 0x200,
    BroadcastId = 0x300,

    ReadDataByIdentifier = {
        ["F1 90"] = "SALGA2EV9HA298784",
        ["F1 24"] = "HPLA-12345-AB",
        ["1E 23"] = "231132",
    },

    Raw = {
        ["10 02"] = "50 02 00 19 01 f4",
        ["22 fa bc"] = "10 33 11",
        ["22 F1 91"] = "62 F1 91" .. ascii("SALGA2EV9HA298784")
    }
}

TC03 = {
    -- no broadcast ID
    RequestId = 0x100,
    ResponseId = 0x200,
    -- BroadcastId = 0x300,

    ReadDataByIdentifier = {
        ["F1 90"] = "SALGA2EV9HA298784",
        ["F1 24"] = "HPLA-12345-AB",
        ["1E 23"] = "231132",
    },

    Raw = {
        ["10 02"] = "50 02 00 19 01 f4",
        ["22 fa bc"] = "10 33 11",
        ["22 F1 91"] = "62 F1 91" .. ascii("SALGA2EV9HA298784")
    }
}

