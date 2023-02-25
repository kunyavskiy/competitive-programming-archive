import java.util.PriorityQueue
import java.util.TreeSet

fun winByFirst(a: List<Int>, len: Int) {
    println("Alessia")
    val x = PriorityQueue<Pair<Int, Int>>(compareBy({ -it.first }, { it.second }))
    x.add(len to 1)
    for (l in a) {
        val t = x.poll()
        require(t.first >= l)
        println("$l ${t.second}")
        System.out.flush()
        val pos = readInt()
        x.add((pos - t.second) to t.second)
        x.add((t.second + t.first - pos - 1) to (pos + 1))
    }
}

fun winBySecond(a: List<Int>, len: Int, winL: Int) {
    println("Bernardo")
    System.out.flush()
    for (i in a.indices) {
        val (l, pos) = readInts()
        val toRemove = if (l < winL) pos else (pos + winL - 1) / winL * winL
        println(toRemove)
        System.out.flush()
    }
}

fun main() {
    val (n, m) = readInts()
    val a = readInts().sortedDescending()
    val winL = a.withIndex().firstOrNull { (index, value) ->
        index >= m / value
    }
    if (winL == null) {
        winByFirst(a, m)
    } else {
        winBySecond(a, m, winL.value)
    }

}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }