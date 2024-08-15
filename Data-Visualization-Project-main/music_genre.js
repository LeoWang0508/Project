function init_music_genre_graph(year){
    d3.csv("./Spotify 2010 - 2019 Top 100(genre).csv").then(data =>{
        data.forEach(d => {
            d.year = Number(d.top_year);
            //d.bpm = Number(d.bpm);
            //d.nrgy = Number(d.nrgy);
            //d.dnce = Number(d.dnce);
            //d.dB = Number(d.dB);
            //d.live = Number(d.live);
            //d.val = Number(d.val);
            //d.dur = Number(d.dur);
            //d.acous = Number(d.acous);
            //d.spch = Number(d.spch);
            d.pop = Number(d.pop);
            d.genre = d.genre
        });
        
        var minYear = d3.min(data, function (d) { return d.year })
        var maxYear = d3.max(data, function (d) { return d.year })
        
        var genre_year = d3.nest()
            .key(function (d) { return d.genre; })
            .key(function(d){return d.year;})
            //.entries(data); 
            .map(data)
        
        var genre = d3.nest()
            .key(function (d) { return d.genre; })
            .map(data)
            .keys()
        
        var year = d3.nest()
            .key(function (d) { return d.year; })
            .map(data)
            .keys()
        
        console.log(genre)
        console.log(year)
        //console.log(year_genre)
        //var year_arr = year_genre.keys()
        //console.log(year_arr)
        var each_genre = genre_year.values()
        var i = 0
        var MaxCountGenre = 0
        var all_genre_data = []
        genre_count = 0
        each_genre.forEach(d => {
            //  console.log(d)
            var this_genre_data = []
            for (var i = 0; i < year.length; i++){
                var item = { 'year': Number(year[i]), 'count': 0 ,'genre':genre[genre_count]}
                var j = 0
                d.values().forEach(dd => {
                    this_genre_has_this_year = Number(d.keys()[j])
                    if (this_genre_has_this_year == Number(year[i]))
                        item['count'] = dd.length
                    if (dd.length > MaxCountGenre)
                        MaxCountGenre = dd.length
                    j += 1
                })
                all_genre_data.push(item)
            }
            //console.log(this_genre_data)
            //all_genre_data.push(this_genre_data)
            genre_count += 1
        })
        //console.log(all_genre_data.length)
        console.log(all_genre_data) 
        //console.log(minYear)
        //console.log(maxYear)

        const MARGIN = { LEFT: 100, RIGHT: 120, TOP: 10, BOTTOM: 130 }
        const WIDTH = 600 - MARGIN.LEFT - MARGIN.RIGHT
        const HEIGHT = 400 - MARGIN.TOP - MARGIN.BOTTOM

        let lineLeft = 0, lineTop = 400;
        let lineTotalWidth = 690, lineTotalHight = 600;
        let lineMargin = { top: 50, right: 30, bottom: 100, left: 20 },
            lineWidth = lineTotalWidth - lineMargin.left - lineMargin.right,
            lineHight = lineTotalHight - lineMargin.top - lineMargin.bottom;
        
        //console.log(lineWidth)
        //console.log(lineHight)

        var tip = d3.tip()
            .attr("class","d3-tip")
            .html(d=>
                "<strong style='color:yellow'>Genre: </strong>" + d.key
            )
        const svg = d3.select("#music-genre-area").append("svg")
                    .attr("width", lineTotalWidth)
                    .attr("height", lineTotalHight)
        svg.call(tip)
        const g = svg.append("g")
            .attr("transform", `translate(${lineMargin.left+50}, ${lineMargin.top})`)
        
        // X label
        g.append("text")
            .attr("x", WIDTH-50)
            .attr("y", lineHight+40)
            .attr("font-size", "15px")
            .attr("text-anchor", "middle")
            .text("Year")

        // Y label
        g.append("text")
            .attr("x", -HEIGHT)
            .attr("y", -40)
            .attr("font-size", "15px")
            .attr("text-anchor", "middle")
            .attr("transform", "rotate(-90)")
            .text("# of musics")

        // X Y Scale
        var xScale = d3.scaleLinear()
                    .domain(d3.extent(all_genre_data, d => d.year))
                    .range([0, lineWidth-35]);
      
        
        var yScale = d3.scaleLinear()
                    .domain([0, MaxCountGenre])
                    .range([lineHight, 0]);
        
        g.append("g")
            .attr("transform", "translate(0," + lineHight + ")")
            .call(d3.axisBottom(xScale));
        
        g.append("g")
            .call(d3.axisLeft(yScale));
        
        var sumstat = d3.nest() 
            .key(d => d.genre)
            .entries(all_genre_data);
        
        console.log(sumstat)
        var color = d3.scaleOrdinal(["#d0743c" ,"#383867", "#C96A23", "#584c77", "#66AFB2", "#a36629", "#92462f", "#79CED7","#b63e36", "#b74a70", "#946943", "#1f77b4", "#ff7f0e","#F5821F", "#2ca02c", "#d62728", "#9467bd", "#8c564b", "#e377c2", "#7f7f7f", "#bcbd22", "#17becf"]);
        
        var lineGenerator = d3.line()
            .x(d => xScale(d.year))
            .y(d => yScale(d.count));
        
        g.selectAll(".line")
            .append("g")
            .attr("class", "line")
            .data(sumstat)
            .enter()
            .append("path")
            .style("stroke", function (d,i) { return color(d.key)})
            .attr("d", function (d) {
                return d3.line()
                    .x(d => xScale(d.year))
                    .y(d => yScale(d.count)).curve(d3.curveCardinal)
                    (d.values)
            })
            .attr("fill", "none")
            .attr("stroke-width", 2)
            .on("mouseover", tip.show)
            .on("mouseout", tip.hide)
        
        g.selectAll("circle")
            .append("g")
            .data(all_genre_data)
            .enter()
            .append("circle")
            .attr("r", 6)
            .attr("cx", d => xScale(d.year))
            .attr("cy", d => yScale(d.count))
            .style("fill", d => color(d.genre))
        
        var legend = d3.select("svg")
            .selectAll('g.legend')
            .data(sumstat)
            .enter()
            .append("g")
            .attr("class", "legend");
        
        legend.append("circle")
            .attr("cx", 700)
            .attr('cy', (d, i) => i * 30 + 100)
            .attr("r", 6)
            .style("fill", d => color(d.key))
        
        legend.append("text")
            .attr("x", 720)
            .attr("y", (d, i) => i * 30 + 105)
            .text(d => d.key)
        
        console.log()
    });
};