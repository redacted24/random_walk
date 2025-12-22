<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a id="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
<h3 align="center">Random Walk</h3>

  <p align="center">
    A simple random walk built with C, rendered with SDL2.
    <br />
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

![randomwalk](https://github.com/user-attachments/assets/3e1b7d9e-5c7d-4cf9-9370-94f04188049e)

A simple random walk built with Simple MediaDirect Layer 2. Choose the number of walks to generate, and visualize it all with nice colors.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

* C
* Simple DirectMedia Layer 2

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

Tested on the Wayland compositor.

**Arch Linux**
- Make sure you have sdl2 installed. If not, please install through yay:
  <br><br>
  ```sh
  yay -S sdl2
  ```
<br>
SDL has migrated to SDL3, but lacks documentation. This is why I still chose to write this project in SDL2.

### Installation

1. Clone the repo to where you want it.
   <br><br>
   ```sh
   git clone https://github.com/redacted24/random_walk
   ```
2. Go into the directory where you cloned the repository. Build the project (makefile).
   <br><br>
   ```sh
   cd random_walk && make
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

`./random_walk.out <num-of-walks>`

<p align="right">(<a href="#readme-top">back to top</a>)</p>
