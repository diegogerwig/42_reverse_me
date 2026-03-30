strings ./level* | grep -v "^[. ]" > levelx_strings.txt
objdump -d ./level* > levelx.asm



DECOMPILER EXPLORER

https://dogbolt.org/

GHIDRA


COMPILAR Y EJECUTAR

gcc source.c -o /tmp/my_levelx
chmod +x /tmp/my_levelx
/tmp/my_levelx



cd $(git rev-parse --show-toplevel)
docker run --rm -it -v $(pwd):/app ubuntu:22.04 bash -c "
 dpkg --add-architecture i386 &&
 apt-get update -q &&
 apt-get install -y libc6:i386 &&
 cp /app/level1/exe/level1 /tmp/level1 &&
 cp /app/level2/exe/level2 /tmp/level2 &&
 cp /app/level3/exe/level3 /tmp/level3 &&
 chmod +x /tmp/level* &&
 bash
"
/tmp/levelX