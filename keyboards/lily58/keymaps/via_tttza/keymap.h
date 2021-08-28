typedef union {
    uint32_t raw;
    struct {
        bool jis    :1;
    };
} persistent_config_t;
