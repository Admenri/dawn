SKIP: FAILED


static uint var_1 = 0u;
void main_1() {
  var_1 = 0u;
  {
    while(true) {
      var_1 = 1u;
      if (true) {
        var_1 = 2u;
        if (false) {
          break;
        } else {
          {
            var_1 = 4u;
          }
          continue;
        }
      }
      var_1 = 3u;
      {
        var_1 = 4u;
      }
      continue;
    }
  }
  var_1 = 5u;
}

void main() {
  main_1();
}

FXC validation failure:
C:\src\dawn\Shader@0x0000021005EF8CA0(6,11-14): error X3696: infinite loop detected - loop never exits

