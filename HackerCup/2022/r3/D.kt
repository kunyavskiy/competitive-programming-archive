private class DSU(n: Int) {
    val p = IntArray(n) { it }
    val size = IntArray(n) { 0 }
    fun get(x: Int) : Int = when {
        p[x] == x -> x
        else -> get(p[x]).also { p[x] = it }
    }
    fun join(a:Int, b: Int) {
        val aa = get(a)
        val bb = get(b)
        if (size[aa] < size[bb]) {
            p[aa] = bb
            size[bb] += size[aa]
        } else {
            p[bb] = aa
            size[aa] += size[bb]
        }
    }
}

private tailrec fun gcd(a:Int, b:Int):Int  = if (b == 0) a else gcd(b, a % b)

private fun solve() {
    val (n, m) = readInts()
    val sets = MutableList(n) { mutableListOf(it) }
    val d = DSU(n)
    val removed = List(m) {
        val (a, b) = readInts().map { it - 1 }
        if (sets[a].size > sets[b].size) {
            val t = sets[a]
            sets[a] = sets[b]
            sets[b] = t
        }
        if (sets[a].isEmpty()) return@List emptyList()
        require(sets[b].isNotEmpty())
        require(d.get(sets[a][0]) != d.get(sets[b][0]))
        val rep = d.get(sets[b][0])
        val toRemove = mutableListOf<Int>()
        for (i in sets[a]) {
            if (i != 0 && d.get(i - 1) == rep) {
                toRemove.add(i)
            }
            if (i != n - 1 && d.get(i + 1) == rep) {
                toRemove.add(i + 1)
            }
        }
        d.join(sets[b][0], sets[a][0])
        sets[b].addAll(sets[a])
        sets[a].clear()
        toRemove.toList()
    }
    val done = removed.flatten().toSet()
    var g = 0
    for (i in 1 until n) {
        if (i !in done) {
            g = gcd(g, i)
        }
    }
    val gs = IntArray(m + 1)
    gs[m] = g
    for (i in removed.lastIndex downTo 0) {
        for (t in removed[i]) {
            g = gcd(g, t)
        }
        gs[i] = g
    }
    val gf = IntArray(n + 1) { Int.MAX_VALUE }
    for (i in gs.indices) {
        gf[gs[i]] = minOf(gf[gs[i]], i)
    }
    println((1..n).sumOf { i ->
        ((0..n) step i).minOf { gf[it] }.let {
            when (it) {
                Int.MAX_VALUE -> -1
                else -> it
            }.toLong()
        }
    })
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }