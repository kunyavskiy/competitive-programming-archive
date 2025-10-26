import kotlin.math.abs
import kotlin.math.absoluteValue

private fun solve() {
    readln()
    val a = readLongs()
    fun check(lim: Long) : Boolean {
        val used = BooleanArray(a.size)
        val dfs = DeepRecursiveFunction { i ->
            if (used[i]) return@DeepRecursiveFunction
            used[i] = true
            if (i > 0 && abs(a[i] - a[i - 1]) <= lim) { callRecursive(i - 1) }
            if (i < a.size - 1 && abs(a[i] - a[i + 1]) <= lim) { callRecursive(i + 1) }
        }
        for (i in a.indices) {
            if (a[i] <= lim) {
                dfs(i)
            }
        }
        return used.all { it }
    }
    var l = 0L
    var r = a.max()
    while (r - l > 1) {
        val m = (l + r) / 2
        if (check(m)) {
            r = m
        } else {
            l = m
        }
    }
    println(r);
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }