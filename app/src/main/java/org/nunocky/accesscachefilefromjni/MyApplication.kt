package org.nunocky.accesscachefilefromjni

import android.app.Application
import java.io.File
import java.io.FileOutputStream

class MyApplication : Application() {
    lateinit var path0: String

    override fun onCreate() {
        super.onCreate()

        path0 = copyResourceIntoCache(R.raw.test, "text.txt")
    }

    /**
     * rawディレクトリ下にあるリソースをキャッシュディレクトリにコピーする
     */
    private fun copyResourceIntoCache(resId: Int, filename: String): String {
        val file = File("$cacheDir/$filename")

        if (!file.exists()) {
            try {
                val inStream = resources.openRawResource(resId)
                val size = inStream.available()
                val buffer = ByteArray(size)
                inStream.read(buffer)
                inStream.close()

                val fos = FileOutputStream(file)
                fos.write(buffer)
                fos.close()
            } catch (e: Exception) {
                throw RuntimeException(e)
            }

        }

        return file.absolutePath
    }

}