Phase 8: Variable Discovery (incremental step)

- Verified with -O0 -g -fno-omit-frame-pointer that local variables in foo() are stored at fixed offsets from RBP.
- Example in the current build:
  - x = -88 from RBP
  - y = -84 from RBP
- The tool now exposes a lightweight API:
  - stackviz_dump_vars(frame_base, vars, count)
- This is an intermediate step toward full DWARF-based recovery, but it works reliably for the current test sample.
