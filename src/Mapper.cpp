#include "Mapper.h"
#include "MapperNROM.h"
#include "MapperSxROM.h"
#include "MapperUxROM.h"
#include "MapperCNROM.h"

namespace sn
{
    NameTableMirroring Mapper::getNameTableMirroring()
    {
        return static_cast<NameTableMirroring>(m_cartridge.getNameTableMirroring());
    }
   
    std::unique_ptr<Mapper> Mapper::createMapper(Mapper::Type mapper_t, sn::Cartridge& cart, std::function<void(void)> mirroring_cb)
    {
//root@Tos:~/git/see/SimpleNES/build# ./SimpleNES ../game/Super.nes
//[Cartridge.cpp:53] Reading ROM from path: ../game/Super.nes
//[Cartridge.cpp:72] Reading header, it dictates:
//[Cartridge.cpp:112] 16KB PRG-ROM Banks: 2 '+banks'
//[Cartridge.cpp:120] 8KB CHR-ROM Banks: 1 '+vbanks'
//[Cartridge.cpp:123] Name Table Mirroring: 1 '+m_nameTableMirroring'
//[Cartridge.cpp:126] Mapper #: 0 '+m_mapperNumber'
//[Cartridge.cpp:129] Extended (CPU) RAM: false 'm_extendedRAM'
//[Cartridge.cpp:143] ROM is NTSC compatible.
        std::unique_ptr<Mapper> ret(nullptr);
        switch (mapper_t)
        {
            case NROM:
                ret.reset(new MapperNROM(cart));
                break;
            case SxROM:
                ret.reset(new MapperSxROM(cart, mirroring_cb));
                break;
            case UxROM:
                ret.reset(new MapperUxROM(cart));
                break;
            case CNROM:
                ret.reset(new MapperCNROM(cart));
                break;
            default:
                break;
        }
        return ret;
    }
}