package com.github.yasharsbsb;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

public class NativePrimeGenerator {

    static {
        String resource = NativePrimeGenerator.class.getResource("/libnative.so").getFile();
        try {
            byte[] bytes = Files.readAllBytes((new File(resource)).toPath());
            Files.write((new File("/tmp/libnative.so")).toPath(), bytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.load("/tmp/libnative.so");
    }

     public native String nextPrime(String inp);
}
