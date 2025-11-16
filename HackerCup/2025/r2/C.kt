private fun solve() {
    val (n, k, m) = readInts()

    val lines = List(m) {
        readInts().drop(1).map { it - 1 }
    }

    data class ExtraVertex(val lineId: Int, val positionId: Int, val length: Int)
    val extraIds = mutableMapOf<ExtraVertex, Int>()

    val g = MutableList(n) { mutableListOf<Int>() }

    fun getExtra(lineId: Int, positionId: Int, length: Int) : Int? {
        if (positionId >= lines[lineId].size) return null
        return extraIds.getOrPut(ExtraVertex(lineId, positionId, length)) {
            val nid = g.size
            val x = mutableListOf<Int>()
            g.add(x)
            if (length % 2 == 1) {
                x.add(lines[lineId][positionId])
                if (length != 1) {
                    getExtra(lineId, positionId + 1, length - 1)?.let { x.add(it) }
                }
            } else {
                getExtra(lineId, positionId, length / 2)?.let { x.add(it) }
                getExtra(lineId, positionId + length / 2, length / 2)?.let { x.add(it) }
            }
            nid
        }
    }

    for (l in lines.indices) {
        for ((index, x) in lines[l].withIndex()) {
            getExtra(l, index + 1, k)?.let { g[x].add(it) }
        }
    }

    val deque = ArrayDeque<Int>()
    deque.add(0)
    val dist = IntArray(g.size) { -1 }
    dist[0] = 0
    while (!deque.isEmpty()) {
        val x = deque.removeFirst()
        val dst = if (x < n) 1 else 0
        for (y in g[x]) {
            if (dist[y] == -1 || dist[y] > dist[x] + dst) {
                dist[y] = dist[x] + dst
                if (dst == 0) {
                    deque.addFirst(y)
                } else {
                    deque.addLast(y)
                }
            }
        }
    }
    println((0 until n).sumOf { (it + 1).toLong() * dist[it] })
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