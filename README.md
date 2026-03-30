strings ./levelx | grep -v "^[. ]" > levelx_strings.txt

objdump -d ./levelx > levelx.asm



GHIDRA

https://dogbolt.org/




COMPILAR Y EJECUTAR

gcc source.c -o my_levelx
./my_levelx

docker run --rm -it -v $(pwd):/app ubuntu:22.04 bash -c "
  dpkg --add-architecture i386 &&
  apt-get update -q &&
  apt-get install -y libc6:i386 &&
  /app/levelx
"