import java.util.PriorityQueue
import java.util.TreeSet

private const val MOD =  1000000007

private data class Client(val id:Int, val day:Int, val cost:Int, val isBuy: Int)

private fun solve(debug: Boolean) {
    val (n, k) = readInts()
    val data = List(n) { readInts() }
    val clients = data.flatMapIndexed { index, it ->
        listOf(
            Client(index, it[0], it[2], 1),
            Client(index, it[1], it[3], 0)
        )
    }.sortedWith(compareBy(
        { it.day },
        { -it.cost },
        { it.isBuy },
        { it.id }
    ))

    data class Edge(val cost:Long, val to:Int)

    val next = Array(2) { arrayOfNulls<Edge>(n) }
    var prevBuy : Client? = null
    for (client in clients) {
        if (prevBuy != null && prevBuy.day == client.day) {
            next[client.isBuy][client.id] = Edge((prevBuy.cost - client.cost).toLong(), prevBuy.id)
        }
        if (client.isBuy == 1) {
            prevBuy = client
        }
    }

    require(next[0].filterNotNull().all { it.cost > 0 })


    val order = (0 until n).sortedWith(compareBy(
        { data[it][0] },
        { data[it][2] },
        { -it }
    )).reversed().toIntArray()


    val best = LongArray(n) { -1 }

    val fin = PriorityQueue(compareByDescending<Long> { it })
    val path = PriorityQueue(compareByDescending(Pair<Long,Int>::first))
    fin.add(-1)
    path.add(-1L to -1)

    for (i in order) {
        best[i] = 0
        for (e in 0..1) {
            next[e][i]?.let {
                require(best[it.to] != -1L) { "$i ${it}"}
                best[i] = maxOf(best[i], best[it.to] + it.cost)
            }
        }
    }
    for (i in 0 until n) {
        next[0][i]?.let {
            path.add(it.cost + best[it.to] to it.to)
        }
    }

    var ans = 0L
    var prev = Long.MAX_VALUE
    var done = 0
    val res = mutableListOf<Long>()
    while (done < k) {
        val topF = fin.peek()!!
        val topP = path.peek()!!
        if (topF < 0 && topP.first < 0) break
        require(topP.first <= prev)
        require(topF <= prev)
        if (topF > topP.first) {
            prev = topF
            done += 1
            ans = (ans + topF) % MOD
            res.add(topF)
            fin.poll()
        } else {
            path.poll()
            var s = topP.second
            var add = topP.first - best[s]
            while (true) {
                val n1 = next[0][s]
                val n2 = next[1][s]
                fin.add(add)
                if (n1 == null || n2 == null) {
                    val nxt = n1 ?: n2 ?: break
                    require(best[s] == best[nxt.to] + nxt.cost)
                    add += nxt.cost
                    s = nxt.to
                    continue
                }
                if (best[s] == best[n1.to] + n1.cost) {
                    path.add(add + n2.cost + best[n2.to] to n2.to)
                    add += n1.cost
                    s = n1.to
                } else {
                    require(best[s] == best[n2.to] + n2.cost)
                    path.add(add + n1.cost + best[n1.to] to n1.to)
                    add += n2.cost
                    s = n2.to
                }
            }
            require(add == topP.first)
        }
    }
    println(ans)
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve(it + 1 == 19)
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }