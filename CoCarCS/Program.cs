using System;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;

namespace CoCarCs
//    // 14217ebb-21e4-40c0-a60a-b708253b30d2
//DEFINE_GUID(IID_IEngine,
//	0x14217ebb, 0x21e4, 0x40c0, 0xa6, 0x0a, 0xb7, 0x08, 0x25, 0x3b, 0x30, 0xd2);



{
    class Program
    {
        //// 2736597a-fe8b-486b-8caa-0b8432f89c3f
        //DEFINE_GUID(CLSID_CoCar,
        //	0x2736597a, 0xfe8b, 0x486b, 0x8c, 0xaa, 0x0b, 0x84, 0x32, 0xf8, 0x9c, 0x3f);

        [ComVisible(true)]
        [ComImport, Guid("2736597A-FE8b-486B-8CAA-0B8432F89C3F")]
        public class Car
        {
        }

        // dd9050f7-6a4c-4f34-a662-1c77a9905c42
        [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("DD9050F7-6A4C-4F34-A662-1C77A9905C42")]
        public interface ICreateCar
        {
            void SetPetName(string petName);
            void SetMaxSpeed(int maxSp);
        }

        ////  823EF5F6-12CE-46D7-BC60-E1C00E3183FE
        [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("823EF5F6-12CE-46D7-BC60-E1C00E3183FE")]
        public interface IStats
        {
            void DisplayStats();
            void GetPetName(ref string petName);
        }

        // 14217EBB-21E4-40C0-A60A-B708253B30D2
        [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("14217EBB-21E4-40C0-A60A-B708253B30D2")]
        public interface IEngine
        {
            void SpeedUp();
            void GetMaxSpeed(ref int curSpeed);
            void GetCurSpeed(ref int maxSpeed);
        }

        [STAThread]
        static void Main(string[] args)
        {
            
            Car myCar = new Car();
            ICreateCar iCrCar = (ICreateCar)myCar;
            IStats pStats = (IStats)myCar;
            IEngine pEngine = (IEngine)myCar;

            Console.WriteLine("Напишите имя: ");
            iCrCar.SetPetName(Console.ReadLine());
            string Carname = "";
            pStats.GetPetName(ref Carname);
            Console.WriteLine("Ваше имя: " + Carname);

            iCrCar.SetMaxSpeed(400);

            pStats.DisplayStats();

            int curSpeed = 0, maxSpeed = 0;


            pEngine.GetMaxSpeed(ref maxSpeed);

            do
            {
                pEngine.SpeedUp();
                pEngine.GetCurSpeed(ref curSpeed);
                Console.WriteLine("Speed is:" + curSpeed);
            } while (curSpeed < maxSpeed);

           

            Console.ReadKey();


        }
    }
}

