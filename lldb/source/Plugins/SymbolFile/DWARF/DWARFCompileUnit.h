//===-- DWARFCompileUnit.h --------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef SymbolFileDWARF_DWARFCompileUnit_h_
#define SymbolFileDWARF_DWARFCompileUnit_h_

#include "DWARFUnit.h"
#include "llvm/Support/Error.h"

class DWARFCompileUnit : public DWARFUnit {
public:
  static llvm::Expected<DWARFUnitSP>
  extract(SymbolFileDWARF *dwarf2Data, lldb::user_id_t uid,
          const lldb_private::DWARFDataExtractor &debug_info,
          lldb::offset_t *offset_ptr);
  void Dump(lldb_private::Stream *s) const override;

  /// Get the data that contains the DIE information for this unit.
  ///
  /// \return
  ///   The correct data (.debug_types for DWARF 4 and earlier, and
  ///   .debug_info for DWARF 5 and later) for the DIE information in
  ///   this unit.
  const lldb_private::DWARFDataExtractor &GetData() const override;

  /// Get the size in bytes of the header.
  ///
  /// \return
  ///     Byte size of the compile unit header
  uint32_t GetHeaderByteSize() const override;

  DIERef::Section GetDebugSection() const override {
    return DIERef::Section::DebugInfo;
  }

private:
  DWARFCompileUnit(SymbolFileDWARF *dwarf2Data, lldb::user_id_t uid);
  DISALLOW_COPY_AND_ASSIGN(DWARFCompileUnit);
};

#endif // SymbolFileDWARF_DWARFCompileUnit_h_
