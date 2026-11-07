import os
import subprocess
import sys
from collections.abc import Iterable

import architectds as ads

nitrofs = ads.NitroFS()
nitrofs.add_nflib_bg_tiled(['assets/graphics/bgtiled'])
nitrofs.add_nflib_sprite_256(['assets/graphics/sprites'])
nitrofs_soundbank_header = nitrofs.add_mmutil(['assets/audio'])
nitrofs.add_bmfont_fnt(['assets/fonts'], 'font')
nitrofs.generate_image()

arm9 = ads.Arm9Binary(
    sourcedirs=['source'],
    libs=['nds9', 'mm9', 'nflib', 'dsf'],
    libdirs=[
        '${BLOCKSDS}/libs/libnds',
        '${BLOCKSDS}/libs/maxmod',
        '${BLOCKSDSEXT}/nflib',
        '${BLOCKSDSEXT}/libdsf',
    ],
    cxxflags='-std=c++23',
)
arm9.add_header_dependencies([nitrofs_soundbank_header])
arm9.generate_elf()

nds_path = 'timerds.nds'
nds = ads.NdsRom(
    binaries=[arm9, nitrofs],
    nds_path=nds_path,
    game_title='TimerDS',
    game_subtitle='Timer and stopwatch for Nintendo DS',
    game_author="angeljreyes on GitHub",
    unit_code=2,
)
nds.generate_nds()

def contains[T](iterable: Iterable[T], *args: Iterable[T]) -> bool:
    """Check that all arguments have at least one element that is contained in `iterable`."""
    for arg in args:
        for element in arg:
            if element in iterable:
                break
        else:
            return False
    return True

# Parameters `-cbj` should be interpreted as `-c -b -j`
args: list[str] = []
for arg in sys.argv[1:]:
    if len(arg) >= 3 and arg.startswith('-'):
        args.extend(f'-{c}' for c in arg[1:])
    else:
        args.append(arg)

if contains(args, ['-r', '--run']) and not contains(args, ['-b', '--build']):
    args.append('-b')

nds.run_command_line_arguments(args)

if contains(args, ['-h', '--help']):
    print(
        '\nTimerDS custom options:\n\n'
            + '  -r / --run : Builds the rom and runs it with `melonDS` or the environment variable NDS_EMULATOR if set.'
    )
else:
    if contains(args, ['-r', '--run']) and os.path.exists(nds_path):
        emulator = os.environ.get('NDS_EMULATOR', 'melonDS')
        subprocess.run([emulator, nds_path], check=False)
