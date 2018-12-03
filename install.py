from pathlib import Path
import urllib.request
import zipfile
import shutil

CWD = Path(".")
libsdl2_path = (CWD / "libsdl2")
if libsdl2_path.exists():
    print(f"Deleting {libsdl2_path}")
    shutil.rmtree(str(libsdl2_path))
else:
    libsdl2_path.mkdir()

libsdl2 = "SDL2-devel-2.0.8", \
          "https://www.libsdl.org/release/SDL2-devel-2.0.8-VC.zip"
libsdl_image = "SDL2-image-devel-2.0.3", \
               "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.3-VC.zip"
libsdl_ttf = "SDL2-ttf-devel-2.0.14", \
             "https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.14-VC.zip"


def download_and_unzip():
    libraries = (libsdl2, libsdl_image, libsdl_ttf)
    for file, url in libraries:
        # Don't download the file again.
        zip_file = CWD / (file + ".zip")
        if not zip_file.exists():
            print(f"Downloading {zip_file}")
            response = urllib.request.urlretrieve(url, file + ".zip")
        else:
            print(f"Already Downloaded {zip_file}")

        print("Unzipping...")
        zip_ref = zipfile.ZipFile(file + ".zip", "r")
        zip_ref.extractall("libsdl2")
        zip_ref.close()
        print("Done")


download_and_unzip()
debug_path = CWD / "x64" / "Debug"
debug_path.mkdir(parents=True, exist_ok=True)
release_path = CWD / "x64" / "Release"
release_path.mkdir(parents=True, exist_ok=True)

x64 = set(libsdl2_path.glob("**/x64"))
dlls = set()

for p in x64:
    dlls = dlls.union(p.glob("**/*.dll"))
    dlls = dlls.union(p.glob("**/*.lib"))

for dll in dlls:
    print(dll)
    shutil.copy(str(dll), str(debug_path))
    shutil.copy(str(dll), str(release_path))


