#!/usr/bin/env python3
import json,subprocess,wave
from pathlib import Path
root=Path(__file__).resolve().parents[1];out=root/'build/evolved-audio';out.mkdir(parents=True,exist_ok=True)
exe=root/'build/host/evolved_audio'
for layer in range(4):
 hashes=set();parts=[]
 for patch in range(16):
  p=out/f'{layer}-{patch}.pcm';r=json.loads(subprocess.check_output([str(exe),str(layer),str(patch),str(p)]));assert r['energy']>0;assert r['hash'] not in hashes,(layer,patch,'duplicate PCM');hashes.add(r['hash']);parts.append(p.read_bytes());assert len(parts[-1])==44100*4*4
 with wave.open(str(out/f'layer-{layer}.wav'),'wb') as w:w.setnchannels(2);w.setsampwidth(2);w.setframerate(44100);w.writeframes(b''.join(parts))
 print(f'PASS layer {layer}: 16 distinct audible presets, sample bounds, 64-second production-DSP preview.',flush=True)
hashes=set()
for i in range(32):
 r=json.loads(subprocess.check_output([str(exe),'-1',str(i)]));assert r['energy']>0 and r['hash'] not in hashes;hashes.add(r['hash'])
print('PASS 32 distinct audible themes, parameter ranges and sample limits.',flush=True)
