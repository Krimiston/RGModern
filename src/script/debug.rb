# zlib License
#
# copyright (C) 2023 Guoxiaomi and Krimiston
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

def debug(b)
  # 使用方法：
  # debug(binding)，在执行到这一句时进入 debug 模式。

  STDOUT.puts '>>> DEBUG MODE <<<'
  loop do
    begin
      STDOUT.print('>: ')
      code = gets
      ret = eval(code, b)
    rescue Exception
      $!.inspect.split("\n").each do |line|
        STDOUT.puts("!> #{line}")
      end
      retry
    end
    if code == "\n"
      STDOUT.puts '>>> EXIT DEBUG <<<'
      break
    else
      STDOUT.puts("=: #{ret}")
    end
  end
end

def debug(b); end if RGM::Config::Build_Mode >= 3 || !$DEBUG
