# Chess[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/IIyCbKA/Chess/blob/main/LICENSE) [![Compiler](https://img.shields.io/badge/Compiler-C++20-blue)](https://isocpp.org) [![UI_framework](https://img.shields.io/badge/UI_framework-Qt6-green)](https://www.qt.io/blog/qt-6.2-lts-released)

## 🔧 Application Overview
🎮 This app is a wrapper for interacting with chess engines. Current version supports **Stockfish**.

**Requirements**:
- Install **Qt6** framework.
- Build Stockfish from [official repo](https://github.com/official-stockfish/Stockfish) or [download pre-built binary](https://github.com/official-stockfish/Stockfish/releases/tag/sf_17) for your device.

**Configuration**:
- Place engine executable in project directory.
- Update path to engine in [`constants.hpp`](include/constants.hpp).
- Update path to engine in [`CMakeLists.txt`](CMakeLists.txt).
- Rebuild the project.

## 📦 Assets Attribution
- Chess pieces from [Maciej Świerczek’s Figma files](https://www.figma.com/community/file/971870797656870866/chess-simple-assets) under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) (I modified original color & aspect ratio).

## ⚠️ Attention
This application includes the Stockfish chess engine, which is free software licensed under the GNU General Public License version 3 ([GPL-3.0](https://www.gnu.org/licenses/gpl-3.0.html)). By using this application with Stockfish, you agree to the terms of the [GPL-3.0](https://www.gnu.org/licenses/gpl-3.0.html) license.


## 📄 Licence
- Project is [MIT licensed](https://github.com/IIyCbKA/Chess/blob/main/LICENSE).
- Chess pieces from [Maciej Świerczek’s Figma files](https://www.figma.com/community/file/971870797656870866/chess-simple-assets) under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

## 🙏 Gratitude
- [Maciej Świerczek](https://www.figma.com/@swierq) for chess pieces.
- All resources and frameworks that I used in this project.