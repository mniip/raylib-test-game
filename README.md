# Setup

```sh
git submodule init
```

# Build and Run Natively

```sh
cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release
cmake --build ./build
./build/raygame
```

# Build for Web

## Build

```sh
emcmake cmake -S . -B ./build_web -DCMAKE_BUILD_TYPE=MinSizeRel -DPLATFORM=Web
cmake --build ./build_web
```

## Run locally

```sh
cd ./build_web
python -m http.server
```

Navigate to [http://localhost:8000/raygame.html](http://localhost:8000/raygame.html)

## Package for Itch.io

```sh
cd ./build_web
cp raygame.html index.html
zip raygame.zip index.html raygame.js raygame.wasm raygame.data
````
