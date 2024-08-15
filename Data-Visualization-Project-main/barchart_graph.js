
function init_barchart_graph(){
    init_draw(0);
    var input_text = document.querySelector('.Text')

    input_text.onfocus=function () {
        if (this.value==='請輸入年份'){
            this.value=''
            this.style.color='#999'
        
        }else {
            this.style.border='1px solid #999'
            this.style.color='black'
        }
    }

    var testInput = document.getElementById('input_year');
    var submitBtn = document.querySelector(".btn");

    var input_value=0
    function FsubmitBtn(input_value) {
        var input = 0
        input = testInput.value
        input_value = parseInt(input)
        //draw(input_value)
        draw_barchart_graph(input_value)
        draw_relation_graph(input_value)
    }

    submitBtn.addEventListener("click", FsubmitBtn);

    function dele() {
        d3.selectAll("#my_bar_chart").select("svg")
		    .remove();
    }

    function init_draw(input_value) {
        d3.csv("Spotify 2010 - 2019 Top 100(new).csv").then(data =>{

            var margin = {top: 10, right: 30, bottom: 30, left: 60},
            width = 800 - margin.left - margin.right,
            height = 515 - margin.top - margin.bottom;

            data.forEach(d => {
                d.year = Number(d.top_year);
            });

            var count_artist = {};
            var count_song = {};
            data.forEach(function(d){
        
                var artist = d.artist;

                d.set = 0
                if (input_value === 0) {
                    if (d.year <= 2019) {
                        if(count_artist[artist]===undefined){
                            count_artist[artist] = 1;
                        } 
                        else{
                            count_artist[artist] = count_artist[artist]+1;
                        }
            
                        if(count_song[artist]===undefined){
                            count_song[artist] = d.title;
                        } 
                        else{
                            count_song[artist] = count_song[artist] +"<br>&emsp;&emsp;&emsp;&thinsp;" + d.title;
                        }
                    }
                }
                else {
                    if(count_artist[artist]===undefined){
                        count_artist[artist] = 0;
                    } 
                    if (d.year === input_value) {
                        if(count_artist[artist]===undefined){
                            count_artist[artist] = 1;
                        } 
                        else{
                            count_artist[artist] = count_artist[artist]+1;
                        }
        
                        if(count_song[artist]===undefined){
                            count_song[artist] = d.title;
                        } 
                        else{
                            count_song[artist] = count_song[artist] +"<br>&emsp;&emsp;&emsp;&thinsp;" + d.title;
                        }
                    }
                }
            });

            data.forEach(function(d){
                var artist = d.artist;
                d.count = count_artist[artist];
                d.song = count_song[artist];
            });

            var tip = d3.tip()
                .attr("class","d3-tip")
                .html(d=>"<strong style='color:yellow'>Artist: </strong>"+d.artist+"<br><br><strong style='color:yellow'>Songs:</strong> <span>"+ d.song +"<br><br><strong style='color:yellow'># of music:</strong> <span>" + d.count)

            var svg = d3.select("#my_bar_chart")
            .append("svg")
                .attr("width", width + margin.left + margin.right)
                .attr("height", height + margin.top + margin.bottom)
            .append("g")
                .attr("transform","translate(" + margin.left + "," + margin.top + ")");

            svg.call(tip);

            // Add X axis
            var max = d3.max(data, function(d) { return d.count; });

            var scaleX = d3.scaleLinear()
                .domain([0,max])
                .range([0, width-90])

    
            svg.append("g")
                .attr("id", "x_axis")
                .attr("class","x axis")  
                .attr("transform", "translate(110," + 30 + ")")
                .call(d3.axisTop(scaleX).ticks(4))

            //x軸文字
            if(input_value === 0) {
                svg.append("text")
                .attr("id", "x_label")
                .attr("transform", "translate(" + (width/2+40) + "," + 5 + ")")
                .style("text-anchor", "middle")
                .style('font-size', '15px')
                .style('font-weight', 'bold')
                .text("# of music from 2010~2019")
            }
            else {
                svg.append("text")
                    .attr("id", "x_label")
                    .attr("transform", "translate(" + (width/2+40) + "," + 5 + ")")
                    .style("text-anchor", "middle")
                    .style('font-size', '15px')
                    .style('font-weight', 'bold')
                    .text("# of music from " + String(input_value))
            }

            data.sort(function(a, b) {
                return d3.ascending(a.count, b.count)
                })

            // Add y axis
            var scaleY = d3.scaleBand()
                .range([height+10000,0])
                .domain(data.map(d => {
                    return d.artist;
                }))
                .padding(0.4)


            svg.append("g")
                .attr("id", "y_axis")
                .attr("class","y axis")
                .attr("transform", "translate(110," + 30 + ")")
                .style('font-size', '12px')
                .style('font-weight', 'bold')
                .call(d3.axisLeft(scaleY));

            //color
            var color = d3.scaleOrdinal(["#d0743c" ,"#383867", "#C96A23", "#584c77", "#66AFB2", "#a36629", "#92462f", "#79CED7","#b63e36", "#b74a70", "#946943", "#1f77b4", "#ff7f0e","#F5821F", "#2ca02c", "#d62728", "#9467bd", "#8c564b", "#e377c2", "#7f7f7f", "#bcbd22", "#17becf"]);
            var bars = svg.selectAll("#my_bar_chart")
                .data(data)
                .enter()
                .append("rect")
                .attr("id", function(d){
                    var j, name='N';
                    for(j=0;j<d.artist.length;j++){
                        if(d.artist[j]==' ') name += '_';
                        else if(d.artist[j].charCodeAt(0)>=65 && d.artist[j].charCodeAt(0)<=90) name += d.artist[j];
                        else if(d.artist[j].charCodeAt(0)>=97 && d.artist[j].charCodeAt(0)<=122) name += d.artist[j];
                    }
                    return name;
                })
                .on("mouseover", tip.show)
                .on("mouseout", tip.hide)
                .attr("transform", "translate(110," + 30 + ")")
                .attr("y", function(d) { return scaleY(d.artist); })
                .attr("width", function(d) { return scaleX(d.count); })
                .attr("height",scaleY.bandwidth())
                .style("fill", function (d,i) { return color(i)})
/*
            bars.on("mouseover", tip.show)
                .on("mouseout", tip.hide);
*/
        });
    }
}

function draw_barchart_graph(input_value) {
    d3.csv("Spotify 2010 - 2019 Top 100(new).csv").then(data =>{

        var margin = {top: 10, right: 30, bottom: 30, left: 60},
        width = 800 - margin.left - margin.right,
        height = 500 - margin.top - margin.bottom;

        data.forEach(d => {
            d.year = Number(d.top_year);
        });

        var count_artist = {};
        var count_song = {};
        data.forEach(function(d){
    
            var artist = d.artist;

            d.set = 0
            if (input_value === 0) {
                if (d.year <= 2019) {
                    if(count_artist[artist]===undefined){
                        count_artist[artist] = 1;
                    } 
                    else{
                        count_artist[artist] = count_artist[artist]+1;
                    }
        
                    if(count_song[artist]===undefined){
                        count_song[artist] = d.title;
                    } 
                    else{
                        count_song[artist] = count_song[artist] +"<br>&emsp;&emsp;&emsp;&thinsp;" + d.title;
                    }
                }
            }
            else {
                if(count_artist[artist]===undefined){
                    count_artist[artist] = 0;
                } 
                if (d.year === input_value) {
                    if(count_artist[artist]===undefined){
                        count_artist[artist] = 1;
                    } 
                    else{
                        count_artist[artist] = count_artist[artist]+1;
                    }
    
                    if(count_song[artist]===undefined){
                        count_song[artist] = d.title;
                    } 
                    else{
                        count_song[artist] = count_song[artist] +"<br>&emsp;&emsp;&emsp;&thinsp;" + d.title;
                    }
                }
            }
        });

        data.forEach(function(d){
            var artist = d.artist;
            d.count = count_artist[artist];
            d.song = count_song[artist];
        });

        var tip = d3.tip()
            .attr("class","d3-tip")
            .html(d=>"<strong style='color:yellow'>Artist: </strong>"+d.artist+"<br><br><strong style='color:yellow'>Songs:</strong> <span>"+ d.song +"<br><br><strong style='color:yellow'># of music:</strong> <span>" + d.count)

        var svg = d3.select("#my_bar_chart").select("svg").select("g");

        svg.call(tip);

        // Add X axis
        var max = d3.max(data, function(d) { return d.count; });

        var scaleX = d3.scaleLinear()
            .domain([0,max])
            .range([0, width-90])


        svg.select("#x_axis")
            .transition()
            .duration(2000)
            .call(d3.axisTop(scaleX).ticks(4))

        //x軸文字
        if(input_value === 0) {
            svg.select("#x_label")
            .transition()
            .duration(2000)
            .text("# of music from 2010~2019")
        }
        else {
            svg.select("#x_label")
            .transition()
            .duration(2000)
            .text("# of music from " + String(input_value))
        }

        data.sort(function(a, b) {
            return d3.ascending(a.count, b.count)
            })

        // Add y axis
        var scaleY = d3.scaleBand()
            .range([height+10000,0])
            .domain(data.map(d => {
                return d.artist;
            }))
            .padding(0.4)


        svg.select("#y_axis")
            .transition()
            .duration(2000)
            .call(d3.axisLeft(scaleY));

        //color
        var i;
        for(i=0;i<data.length;i++){
            var name = 'N', j;
            for(j=0;j<data[i].artist.length;j++){
                if(data[i].artist[j]==' ') name += '_';
                else if(data[i].artist[j].charCodeAt(0)>=65 && data[i].artist[j].charCodeAt(0)<=90) name += data[i].artist[j];
                else if(data[i].artist[j].charCodeAt(0)>=97 && data[i].artist[j].charCodeAt(0)<=122) name += data[i].artist[j];
            }
            var new_data=[];
            for(j=0;j<svg.selectAll("#"+name).size();j++){
                new_data.push({"artist": data[i].artist, "song": data[i].song, "count": data[i].count});
            }
            svg.selectAll("#"+name).data(new_data);
            svg.selectAll("#"+name)
            .transition()
            .duration(2000)
            .attr("y", function(d) { return scaleY(d.artist); })
            .attr("width", function(d) { return scaleX(d.count); })
            .attr("height",scaleY.bandwidth())
        }
    });
}
