project('jogo', 'cpp')

sdl2 = dependency('sdl2')
sdl2_image = dependency('SDL2_image')

cxx = meson.get_compiler('cpp')
boost_dep = [
    cxx.find_library('boost_system'),
    cxx.find_library('boost_filesystem'),
]

includes = include_directories('include')
srcs = [
	'src/main.cc',
	'src/controller.cc',
	'src/view.cc',
	'src/input.cc',
	'src/character.cc',
	'src/Scenary_elements.cc',
	'src/monster.cc',
	'src/projectiles.cc',
]


executable('jogo',
	srcs,
	include_directories: includes,
	dependencies: [sdl2, sdl2_image, boost_dep],
)
