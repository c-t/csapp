Investigation Notes
foo():

push rbp mov rsp, rbp sub rsp, 0x20

Observed:

RBP = 0x7fffffffd530 RSP = 0x7fffffffd510

Frame Size = 32 bytes

[RBP] Saved RBP

[RBP+8] Return Address

Arguments arrive via: RDI RSI

Compiler spills: a -> rbp-0x14 b -> rbp-0x18

Locals: x -> rbp-0x8 y -> rbp-0x4