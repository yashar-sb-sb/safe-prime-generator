package com.github.yasharsbsb;

import java.io.FileOutputStream;
import java.io.InputStream;

public class NativePrimeGenerator {

    static {
        loadNativeLibrary();
    }

     public native String nextPrime(String inp);

    private static boolean NATIVE_LIBRARY_LOADED = false;

    static synchronized void loadNativeLibrary () {
        String lib = "/tmp/libnative.so";
        if (!NATIVE_LIBRARY_LOADED) {
            InputStream in = NativePrimeGenerator.class.getResourceAsStream ("/libnative.so");
            try {

                int read;
                byte[] bytes = new byte[1024];
                FileOutputStream outputStream = new FileOutputStream (lib);

                while ((read = in.read (bytes)) != -1) {
                    outputStream.write (bytes , 0 , read);
                }
                outputStream.close ();
                System.load (lib);
                NATIVE_LIBRARY_LOADED = true;
            } catch (Exception e) {
                System.out.println ("Faile to load file : " + lib);
            }
        }
    }
}
