# cs2-external

> **Base. Not a working external.** This is a snapshot of a CS2 external ESP codebase that **does not currently build / run cleanly against the live game.** CS2's memory layout drifts whenever Valve ships a patch, so by the time you clone this the offsets are already stale. **You will need to update offsets, re-run the dumper, and probably fix build warnings before anything works.** Treat this as a reference / starting point.
>
> **Educational use only.** External cheats violate [Counter-Strike 2's EULA](https://store.steampowered.com/subscriber_agreement/) and will VAC-ban your Steam account on protected servers. Published here as a learning resource for reverse-engineering, process memory access, and overlay rendering techniques. Don't run it against competitive matchmaking.

---

## Credits

This project is **not original work**. All real credit belongs to:

- **[IMXNOOBX](https://github.com/IMXNOOBX)** — author of the upstream project [cs2-external-esp](https://github.com/IMXNOOBX/cs2-external-esp). The entire codebase, UI, engine, config system, and build pipeline is theirs. Years of ongoing maintenance. Go star the real repo.
- **[a2x](https://github.com/a2x)** — author of the [cs2-dumper](https://github.com/a2x/cs2-dumper), the offset-generation tool this project depends on to stay compatible with CS2 updates. Without the dumper, every game patch would mean a day of manual signature-scanning.

See [`UPSTREAM_README.md`](./UPSTREAM_README.md) for the original project's documentation (showcase, feature list, contributor list).

If you're looking for a working, actively-maintained version — go to the upstream repo. This mirror exists purely for personal snapshots / archival / hacking on an isolated copy.

## License

**[CC BY-NC 4.0](./LICENSE)** — inherited from upstream. You must give credit to IMXNOOBX and the respective contributors when redistributing or forking, and you may not use it commercially.

## What's here

Standard C++ Visual Studio project. Loosely:

```
src/
├── core/        — engine, logger, memory access, offset structures
├── external/    — bundled deps (imgui, nlohmann/json, curl, AsyncLogger, custom timer/lib)
├── gui/         — new menu + render pipeline, bundled SF Pro font
├── config/      — settings serialization
├── updater/     — auto-update stub
├── common.cpp   — shared helpers
├── main.cpp     — entry point
└── src.vcxproj  — Visual Studio project
cs2-external-esp.sln — top-level solution
scripts/              — build.bat + helper PowerShell / batch files
.github/workflows/    — CI (auto-build, release, codeberg/gitlab mirror, typo check)
assets/               — font + weapon icon atlases (SFD format)
tools/cs2-phys-extractor/ — map geometry extractor (reads game VPK + emits .opt files)
```

## What's **not** here (deliberately excluded)

| Path | Why excluded |
|---|---|
| `maps/*.opt` | 694 MB of extracted game geometry. Several files exceed GitHub's 100 MB per-file limit. Regenerate them with `scripts/extract_opt.bat` or the tool in `tools/cs2-phys-extractor` after installing CS2. |
| `.vs/` | Visual Studio local cache (IPCH files alone are 1.5 GB) |
| `x64/`, `src/x64/` | Build output |
| `*.log` | Runtime logs (humanize, rcs, autowall) |
| Inner `.git/` dirs inside `src/external/*` | Submodules were materialized as regular directories; their inner git history isn't preserved. If you want proper submodule tracking, delete those dirs and re-add via `git submodule add`. See [`.gitmodules`](./.gitmodules) for the upstream URLs. |

## Build (if you want to try anyway)

Prerequisites:

- **Visual Studio 2022** or later with the "Desktop development with C++" workload
- **Windows 10/11 x64**
- **Latest VC++ redistributable** installed

Steps:

1. Clone this repo.
2. Open `cs2-external-esp.sln` in Visual Studio.
3. Set the build configuration to **`x64 - Release`**.
4. Build. Expect compiler warnings and probably linker errors — this is a stale base.
5. If it builds, the output binary lands in `x64/Release/`.
6. To actually run it against the live game you'll need to:
   - Pull the latest offsets by running the a2x dumper (see [a2x/cs2-dumper](https://github.com/a2x/cs2-dumper))
   - Replace / update the offset structures in `src/core/offsets/`
   - Rebuild
   - Run `cs2-external-esp.exe` **after** launching CS2 in **borderless windowed** mode

## Status

This is a dead snapshot. Pull requests get ignored here — upstream them to [IMXNOOBX/cs2-external-esp](https://github.com/IMXNOOBX/cs2-external-esp) instead, where they'll actually land.

If something major changes about CS2's memory layout, assume this repo is further broken.
