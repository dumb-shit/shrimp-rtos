# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/project/shrimp-rtos/shrimp_rtos/MDK-ARM/tmp/shrimp+shrimp"
  "E:/project/shrimp-rtos/shrimp_rtos/MDK-ARM/tmp/1"
  "E:/project/shrimp-rtos/shrimp_rtos/MDK-ARM/tmp/shrimp+shrimp"
  "E:/project/shrimp-rtos/shrimp_rtos/MDK-ARM/tmp/shrimp+shrimp/tmp"
  "E:/project/shrimp-rtos/shrimp_rtos/MDK-ARM/tmp/shrimp+shrimp/src/shrimp+shrimp-stamp"
  "E:/project/shrimp-rtos/shrimp_rtos/MDK-ARM/tmp/shrimp+shrimp/src"
  "E:/project/shrimp-rtos/shrimp_rtos/MDK-ARM/tmp/shrimp+shrimp/src/shrimp+shrimp-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/project/shrimp-rtos/shrimp_rtos/MDK-ARM/tmp/shrimp+shrimp/src/shrimp+shrimp-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/project/shrimp-rtos/shrimp_rtos/MDK-ARM/tmp/shrimp+shrimp/src/shrimp+shrimp-stamp${cfgdir}") # cfgdir has leading slash
endif()
