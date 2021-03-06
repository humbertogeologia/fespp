1. BUILD ParaView (known to work on Linux with ParaView 5.4.1)
2. BUILD Fesapi (with static linking on HDF5 libraries) v0.13.0.0 : https://github.com/F2I-Consulting/fesapi/archive/v0.13.0.0.tar.gz
3. CONFIGURE Fespp with CMAKE
You should fill in the following variables
   * FESAPI_DIR:PATH=../install
A FindFesapi script will automatically use the above variable to set the FESAPI_INCLUDE and FESAPI_LIBRARY variables (visible in advanced mode)
   * ParaView_DIR:PATH=../PV5-4_Build/install/lib/cmake/paraview-5.4 (or, on windows, the cmake build directory of your built paraview from source)
   * If Qt has been built with ParaView, Qt5_DIR:PATH=../PV5-4_Build/install/lib/cmake/Qt5 else you should reference to your own Qt version (for example C:/Users/Philippe/appli/qt/Qt5.9.5/5.9.5/msvc2013_64/lib/cmake/Qt5)
4. GENERATE the build solution with CMAKE once the CONFIGURE step is OK
5. BUILD the solution generated by CMAKE
6. COPY the folllowing built libraries in the Paraview bin folder. On Linux
   * <span>libFesapiCpp.so</span> (from Fesapi built)
   * libFesapiCpp.so.0.13 (from Fesapi built)
   * libFesapiCpp.so.0.13.0 (from Fesapi built)
   * <span>libFespp.so</span> (from Fespp built)
or on Windows
   * <span>FesapiCpp.0.13.0.0.dll</span> (from Fesapi built)
   * <span>Fespp.dll</span> (from Fespp built)
7. Run the Paraview server (Caution : use **MPI** build of ParaView!!!) : mpirun -np 8 ./pvserver
8. Run the Paraview client : ./paraview
9. Connect the Client to the Server
On client side : File->Connect...  and then fill in the required fields.
10. Loading of the Fespp plugins (**on both client and server sides!!!**)
Menu Tools->Manage plugins...and then select and Load <span>libFespp.so</span>
11. You can now load a RESQML file (epc document)
    * via epc load manager (icon)
Partial object support and improved memory management (only what is visualized)
    * standard File->open file
No partial object support and all data are loaded in memory even if not wisualized.
