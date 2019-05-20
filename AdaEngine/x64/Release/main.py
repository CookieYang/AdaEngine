import AdaEngine

class AdaApplication(AdaEngine.Application):
    def doInit(self):
      print("engine has been init")
    def doRun(self):
        print("I am running")

def main():
  app = AdaApplication()
  app.Initilize()
  app.Run()
  
if __name__ == '__main__':
  main()