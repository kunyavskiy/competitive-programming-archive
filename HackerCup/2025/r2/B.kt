
private fun check(prizes: List<Int>, counts: List<Int>): Boolean {
    val cnt = counts.flatMapIndexed { index, it -> List(it) { index + 1 }  }
    if (cnt.last() > prizes.size) return false

    var ptr = 0
    var demand = 0L
    var smalls = 0L
    for (k in 0 until cnt.size) {
        demand += cnt[k]
        while (ptr < prizes.size && prizes[ptr] <= k + 1) {
            smalls += prizes[ptr]
            ptr++
        }
        if (demand > smalls + (k+1).toLong() * (prizes.size - ptr)) {
            return false
        }
    }

    return true
}

private fun solve() {
    val (n, m) = readInts()
    val a = readInts().groupingBy { it }
        .eachCount().toList()
        .sortedByDescending { it.first }.map { it.second }
    val b = readInts().sorted()

    var l = 0
    var r = a.size + 1
    while (r - l > 1) {
        val m = (l + r) / 2
        if (check(b, a.take(m).reversed())) {
            l = m
        } else {
            r = m
        }
    }
    println(a.take(l).sum())

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