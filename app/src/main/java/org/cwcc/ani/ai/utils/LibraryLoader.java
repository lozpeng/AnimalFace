package org.cwcc.ani.ai.utils;

import org.cwcc.ani.ai.log.Logger;

/**
 * java 加载jni so库
 */
public abstract class LibraryLoader {

    private static final String TAG = "AniAI-LibraryLoader";

    private static volatile LibraryLoader loader=new SystemLibraryLoader();

    private static boolean loaded;

    /**
     * Set the library loader that loads the shared library.
     *
     * @param libraryLoader the library loader
     */
    public static void setLibraryLoader(LibraryLoader libraryLoader) {
        loader = libraryLoader;
    }


    public static synchronized void load() {
        try {
            if (!loaded) {
                loader.load("ani");
                loaded = true;
            }
        } catch (UnsatisfiedLinkError error) {
            loaded = false;
            String message = "Failed to load native shared library.";
            Logger.e(TAG, message, error);
        }
    }
    public abstract void load(String name);

    private static class SystemLibraryLoader extends LibraryLoader {
        @Override
        public void load(String name) {
            System.loadLibrary(name);
        }
    }
}
