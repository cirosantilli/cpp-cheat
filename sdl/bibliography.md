# Bibliography

<http://www.willusher.io/pages/sdl2/>

Pong <https://github.com/chaficnajjar/21st-century-pong>

## Official examples

Ubuntu 15.10 packages tons of examples under `/usr/share/doc/libsdl2-dev/examples.tar.gz`, which are actually the tests under `test/` of the main tree: <http://hg.libsdl.org/SDL>

Those examples seem to use files from other places of the build tree, in particular:

- `build-scripts/` is needed for `./configure` before `make`
- some examples (`testgl`) still fail because they include headers directly from the tree... Remove those from the `Makefile`

## Inspiration

- <https://www.youtube.com/watch?v=LrEvoKI07Ww>

## Tutorials

- 57 videos from techcplusplusguy from 2012: <https://www.youtube.com/playlist?list=PL949B30C9A609DEE8> He's nice, but you know, videos.
