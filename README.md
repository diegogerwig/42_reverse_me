strings ./level1 | grep -v "^[. ]" > strings.txt

objdump -d ./level1 > level1.asm



GHIDRA

https://dogbolt.org/




COMPILAR Y EJECUTAR

gcc source.c -o my_level1
./my_level1

docker run --rm -it -v $(pwd):/app ubuntu:22.04 bash -c "
  dpkg --add-architecture i386 &&
  apt-get update -q &&
  apt-get install -y libc6:i386 &&
  /app/level1
"