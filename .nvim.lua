local bin = vim.env.WONDERFUL_TOOLCHAIN .. "/toolchain/gcc-arm-none-eabi/bin"

vim.lsp.config("clangd", {
    cmd = {
        "clangd",
        "--query-driver=" .. bin .. "/arm-none-eabi-g++," .. bin .. "/arm-none-eabi-gcc",
    }
})
