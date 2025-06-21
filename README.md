# 🌀 PixelPilot

PixelPilot is a C++ image processing engine powered by a custom DSL (domain-specific language) and designed to scale from simple CPU-based filters to full GPU-accelerated shader pipelines using OpenGL.

## 🚀 Features

- 🖼 Load and save JPG/PNG images using `stb_image`
- 🧠 Define image filters using your own DSL file: grayscale,blur 5,sharpen 2
- 🧱 Apply grayscale, blur, and sharpen filters on CPU
- 📜 Custom DSL parser to dynamically build filter pipelines
- ⚙️ CMake-based build system
- 🔥 Future roadmap: DSL → auto-generate GLSL shaders and run on GPU


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
Let me know if you want this:
- Saved as a file you can copy-paste
- With a specific GitHub repo link filled in
- Or if you want to add install instructions for Homebrew/dependencies

And just say the word when you're ready to jump to the **OpenGL shader step**!



