// #include <cstdlib>
// #include <filesystem>
// #include <iostream>

// #include "idk_assert.hpp"
// #include "idk_cppscript.hpp"
// #include "idk_dynamiclib.hpp"


// namespace fs = std::filesystem;


// static std::string
// idk_genCompileCommand( const std::string &compiler,
//                        const std::string &cppstd,
//                        const std::string &inpath,
//                        const std::string &outpath,
//                        const std::string &includepath,
//                        const std::string &libpath )
// {
//     std::string cmd =  compiler + " ";
//                 cmd += "-std=" + cppstd + " ";
//                 cmd += inpath + " ";
//                 cmd += "-shared -fPIC ";
//                 cmd += "-o " + outpath + " ";
//                 cmd += "-I" + includepath + " -L" + libpath + " ";
//                 cmd += "-lidk -lIDKGraphics -lIDKGameEngine ";

//     return cmd;
// }



// void
// idk::RuntimeScript::_load( const std::string &filepath )
// {
//     m_filepath = filepath;

//     fs::path path(filepath);
//     m_name = path.stem();

//     m_libpath = "IDKGE/temp/" + path.relative_path().stem().string() + ".so";

//     std::string cmd = idk_genCompileCommand(
//         "g++",
//         "c++17",
//         m_filepath,
//         m_libpath,
//         "../include/",
//         "../lib/"
//     );

//     std::cout << "Compiling script: \"" << cmd << "\"\n";
//     int result = std::system(cmd.c_str());
//     IDK_ASSERT("Error compiling script", result == 0);

//     m_lib   = idk::dynamiclib::loadObject(m_libpath.c_str());
//     m_entry = idk::dynamiclib::loadFunction(m_lib, "idk_ScriptMain");
//     m_ready = true;
// }


// void
// idk::RuntimeScript::_unload()
// {
//     idk::dynamiclib::unloadObject(m_lib);
//     // fs::remove(m_libpath);
//     m_ready = false;
// }



// idk::RuntimeScript::RuntimeScript( const std::string &filepath )
// {
//     this->_load(filepath);
// }


// idk::RuntimeScript::RuntimeScript( const RuntimeScript &s )
// :   m_filepath  (s.m_filepath),
//     m_libpath   (s.m_libpath),
//     m_lib       (nullptr),
//     m_entry     (nullptr),
//     m_ready     (s.m_ready)
// {
//     this->_load(m_filepath);
// }


// idk::RuntimeScript::RuntimeScript( RuntimeScript &&s )
// :   m_filepath  (s.m_filepath),
//     m_libpath   (s.m_libpath),
//     m_lib       (nullptr),
//     m_entry     (nullptr),
//     m_ready     (s.m_ready)
// {
//     s.m_lib   = nullptr;
//     s.m_entry = nullptr;
//     s.m_ready = false;
// }


// idk::RuntimeScript::~RuntimeScript()
// {
//     if (this->is_ready())
//         this->_unload();
// }


// idk::RuntimeScript
// idk::RuntimeScript::operator = ( const idk::RuntimeScript &s )
// {
//     if (this != &s)
//     {
//         m_filepath = s.m_filepath;
//         m_libpath  = s.m_libpath;

//         if (this->is_ready())
//             this->_unload();

//         this->_load(s.m_filepath);
//     }

//     return *this;
// }



// int
// idk::RuntimeScript::execute( idk::EngineAPI &api, int obj_id, int other_id )
// {
//     return idk::dynamiclib::call<int, idk::EngineAPI &, int, int>(m_entry, api, obj_id, other_id);
// }


// void
// idk::RuntimeScript::reload()
// {
//     if (this->is_ready())
//         this->_unload();

//     this->_load(m_filepath);
// }

