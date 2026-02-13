env = SConscript("godot-cpp/SConstruct")

env.Append(CPPPATH = ['src/', 'src/Nodes/', 'src/Resources/', 'src/Resources/StaticData/'])
sources = Glob('src/*.cpp') + Glob('src/Nodes/*.cpp') + Glob('src/Resources/*.cpp') + Glob('src/Resources/StaticData/*.cpp')

library = env.SharedLibrary('demo/bin/DarrylBD99_CCS{}{}'.format(env["suffix"], env['SHLIBSUFFIX']), source = sources)

Default(library)