project('jogo', 'cpp')

sdl2 = dependency('sdl2')
sdl2_image = dependency('SDL2_image')

includes = include_directories('include')
srcs = [
	'src/main.cc',
	'src/controller.cc',
	'src/view.cc',
	'src/input.cc',
	'src/character.cc',
	'src/Scenary_elements.cc',
]

executable('jogo',
	srcs,
	include_directories: includes,
	dependencies: [sdl2, sdl2_image]
)
