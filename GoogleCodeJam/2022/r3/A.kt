private fun getCycles(inp: IntArray) : IntArray {
    val result = IntArray(inp.size) { -1 }
    var cid = 0
    for (i in inp.indices) {
        if (result[i] == -1) {
            cid++;
            var j = i
            var l = 10
            while (result[j] == -1) {
                result[j] = cid
                j = inp[j]
                l--
                if (l == 0) break
            }
        }
    }
    return result
}

private fun solve(n:Int) {
    var input = readInts().map { it - 1 }.toIntArray()
    while (true) {
        println(getCycles(input).joinToString(" "))
        System.out.flush()
        when (readInt()){
            1 -> return
            -1 -> System.exit(0)
            0 -> input = readInts().map { it - 1 }.toIntArray()
        }
    }
}


fun main() {
    val (t, n, k) = readInts()
    repeat(t) {
        solve(n)
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }