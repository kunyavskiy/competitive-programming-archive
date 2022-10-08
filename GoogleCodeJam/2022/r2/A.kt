import kotlin.math.*
import kotlin.system.*

private tailrec fun value(x: Int, y: Int, n: Int, add: Int = 0) : Int = when {
    x == 0 -> y + add
    y == n - 1 -> n - 1 + x + add
    x == n - 1 -> 3 * (n - 1) - y + add
    y == 0 -> 4 * (n - 1) - x + add
    else -> value(x - 1, y - 1, n - 2, add + 4 * (n - 1))
}

private tailrec fun position(value: Int, n: Int, depth: Int = 0) : Pair<Int, Int> = when {
    value <= (n - 1) -> depth to value + depth
    value <= 2 * (n - 1) -> value - (n - 1) + depth to n - 1 + depth
    value <= 3 * (n - 1) -> n - 1 + depth to 3 * (n - 1) - value + depth
    value < 4 * (n - 1) -> 4 * (n - 1) - value + depth to depth
    else -> position(value - 4 * (n - 1), n - 2, depth + 1)
}


private fun solve() {
    val (n, k) = readInts()
    val tx = n / 2
    val ty = n / 2
    fun dist(x: Int, y: Int) = abs(x - tx) + abs(y - ty)
    val curl = dist(0, 0)
    if (k < curl || k % 2 != curl % 2) {
        println("IMPOSSIBLE")
        return
    }
    var l = 0
    var r = n * n
    while (r - l > 1) {
        val m = (l + r) / 2
        val (x, y) = position(m, n)
        if (dist(x, y) + m > k) {
            r = m
        } else {
            l = m
        }
    }
    var (cx, cy) = position(l, n)
    val dirs = listOf(0 to 1, 1 to 0, 0 to -1, -1 to 0)
    val ans = mutableListOf(l)
    var curlen = l
    var curval = l
    while (value(cx, cy, n) != n * n - 1) {
        for ((dx, dy) in dirs) {
            val nx = cx + dx
            val ny = cy + dy
            if (nx in 0 until n && ny in 0 until n && dist(nx, ny) + curlen + 1 == k) {
                val nval = value(nx, ny, n)
                //require(position(nval, n) == nx to ny) {"n = $n, nx = $nx, ny = $ny, nval = $nval, ${position(nval, n)}" }
                if (nval >= curval) {
                    curlen++
                    curval = nval
                    cx = nx
                    cy = ny
                    ans.add(nval)
                }
            }
        }
    }
    ans.zipWithNext().filter { it.first + 1 != it.second }.let {
        println(it.size)
        println(it.joinToString("\n") { "${it.first+1} ${it.second+1}" })
    }
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        measureTimeMillis {
            solve()
        }
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }