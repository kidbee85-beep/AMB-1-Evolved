from pathlib import Path
from urllib.request import urlopen
ROOT = Path(__file__).resolve().parents[1]
BASE = "https://amb1-evolved.sugarypixie10.chatgpt.site/"
FILES = ["audio/layer-0.wav", "audio/layer-1.wav", "audio/layer-2.wav", "audio/layer-3.wav", "install/amb1-evolved-e1.fwsc", "install/amb-1.2.fwsc", "assets/AMB1-Evolved-Vorstellung-DE.mp4"]
for name in FILES:
    path = ROOT / "dist" / name
    path.parent.mkdir(parents=True, exist_ok=True)
    with urlopen(BASE + name) as response:
        path.write_bytes(response.read())
    print(name)
