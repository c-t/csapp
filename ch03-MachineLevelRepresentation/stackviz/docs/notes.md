# StackViz notes

## Phase status

- Phase 0: Investigation — complete
- Phase 1: Frame Inspector — complete
- Phase 2: Memory Walker — complete
- Phase 3: ASCII Stack Visualizer — complete
- Phase 4: Frame Chain Walker — complete
- Phase 5: Backtrace Engine — complete
- Phase 6: Symbol Resolution — complete
- Phase 7: Recursion Visualization — complete
- Phase 8: Variable Discovery — implemented as an explicit offset-based prototype
- Phase 9: Source Mapping — implemented via `addr2line` and ELF-relative address resolution

## Implementation notes

- Verified with `-O0 -g -fno-omit-frame-pointer` that local variables in `foo()` are stored at fixed offsets from `RBP`.
- Example in the current build:
  - `x = -88` from `RBP`
  - `y = -84` from `RBP`
- The tool exposes a lightweight API:
  - `stackviz_dump_vars(frame_base, vars, count)`
- This is an intermediate step toward full DWARF-based recovery, but it works reliably for the current test sample.
