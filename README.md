# 🌀 PixelPilot

PixelPilot is a C++ image processing engine powered by a custom DSL (domain-specific language) and designed to scale from simple CPU-based filters to full GPU-accelerated shader pipelines using OpenGL.

## 🚀 Features

## 🛠️ Features

- ✅ CPU-based image processing pipeline (`image_pipeline/`)
  - Uses `stb_image` for loading and saving images.
  - Supports basic filters like grayscale, blur, and sharpen on CPU.
  
- ⚡ GPU-accelerated processing pipeline (`pixel_plot/`)
  - Uses **OpenGL** + **GLFW** + **GLAD**.
  - Parses a custom `.dsl` file and generates GLSL shaders on the fly.
  - Realtime shader effects on textures.


## 💻 Getting Started

### 🔧 Prerequisites

- macOS / Linux (tested)
- C++17
- CMake ≥ 3.14
- stb_image / stb_image_write
- GLFW + GLAD (for GPU phase)
- Git

### 🛠 Build & Run (CPU Version)

```bash
git clone https://github.com/yourusername/PixelPilot.git
cd PixelPilot
mkdir build && cd build
cmake ..
cmake --build .
./ImagePipeline
```

🧪 Test Output
Check the result:
- open ../assets/output.jpg

🔮 Roadmap

 - CPU image processing (grayscale, blur, sharpen)
 - Custom DSL interpreter
 - Generate GLSL shaders from DSL
 - Apply filters via GPU fragment shaders
 - Live preview and real-time effects
 
📖 License MIT — free to use, remix, and build on.

---
🌟 Future Work

- Implement real blur and sharpen kernels in GLSL.
- Add more DSL commands like brightness, contrast, invert.
- Live reload of DSL during runtime.
- GUI frontend to select filters.

📸 Credits

- Shinchan sample image generated via AI.
- Inspired by real-time image editors and shader playgrounds.

🧑‍💻 Author : Made with ❤️ by Mohit Assudani



