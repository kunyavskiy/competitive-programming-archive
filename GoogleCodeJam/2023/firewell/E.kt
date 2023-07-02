public inline fun <T, R : Comparable<R>> Iterable<T>.maxBy(selector: (T) -> R): T? {
    return maxByOrNull(selector)
}


private fun solve() {
    val (n, l) = readInts()
    for (i in 1 until n) {
        println("$i ${i % n + 1}")
    }
    var c = n - 1
    l@ for (i in 1..n) {
        for (j in n downTo i + 2 ) {
            if (c == l) break@l
            println("$i $j")
            c++
        }
    }
    System.out.flush()

    val data = List(n) { mutableListOf<Int>() }
    repeat(l) {
        val (u, v) = readInts().map { it - 1 }
        data[u].add(v)
        data[v].add(u)
    }

    val big = data.indices.filter { data[it].size == n - 1 }.take(n - 3)
    val dataFiltered = data.mapIndexed { index, g -> g.filter { it !in big && index !in big } }
    val big2 = dataFiltered.indices.maxBy { dataFiltered[it].size }?.takeIf { dataFiltered[it].size > 2 || dataFiltered.none { it.size == 1 }}
    val dataFiltered2 = dataFiltered.mapIndexed { index, g -> g.filter { it != big2 && index != big2 } }
    require(dataFiltered2.all { it.size <= 2 })
    var cur = dataFiltered2.indexOfFirst { it.size == 1 }
    var prev = -1
    val ans = mutableListOf<Int>()
    while (true) {
        ans.add(cur)
        val next = dataFiltered2[cur].firstOrNull { it != prev } ?: break
        prev = cur
        cur = next
    }
    if (big2 != null) {
        if (data[big2].contains(cur)) {
            ans.add(big2)
        } else if (data[big2].contains(ans[0])) {
            ans.add(big2, 0)
        } else {
            require(false)
        }
    }
    ans.addAll(big)
    println(ans.map { it + 1 }.joinToString(" "))
    System.out.flush()
}

fun main() {
    repeat(readInt()) {
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }