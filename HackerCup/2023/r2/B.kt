private fun solve() : Int {
    val n = readInt()
    val aa = readInts()
    val bb = readInts()
    val a = (aa + bb + aa).toIntArray()
    val b = (bb + aa + bb).toIntArray()
    val gs = IntArray(a.size) {
        when {
            a[it] < b[it] -> 0
            a[it] > b[it] -> 2
            else -> 1
        }
    }
    val oa = IntArray(gs.size)
    var cur = 0
    for (i in gs.size - 1 downTo 0) {
        if (gs[i] == 2) {
            cur++
        } else {
            cur = 0
        }
        oa[i] = cur
    }
    cur = 0
    var ans = Int.MAX_VALUE
    for (i in gs.size - 1 downTo 0) {
        if (gs[i] == 0) {
            cur++
        } else {
            cur = 0
        }
        if (cur == n / 2 && i + n <= gs.size) {
            if (n % 2 == 1 && gs[i + n / 2] != 1) continue
            if (oa[i + (n + 1) / 2] < n / 2) continue
            if ((0 until n).all { a[i + it] == b[i + n - it - 1] })
                ans = minOf(ans, i)
        }
    }
    return if (ans == Int.MAX_VALUE) -1 else ans
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        println(solve())
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }