function init_relation_graph(year){
    let RLeft = 800, RTop = 100;
    let RTotalWidth = 560, RTotalHeight = 500;
    let RMargin = {top: 20, right: 45, bottom: 10, left: 85},
        RWidth = RTotalWidth - RMargin.left - RMargin.right, 
        RHeight = RTotalHeight - RMargin.top - RMargin.bottom;


    d3.csv("./Spotify 2010 - 2019 Top 100(new).csv").then(data =>{
        data.forEach(d => {
            d.year = Number(d.top_year);
            d.bpm = Number(d.bpm);
            d.nrgy = Number(d.nrgy);
            d.dnce = Number(d.dnce);
            d.dB = Number(d.dB);
            d.live = Number(d.live);
            d.val = Number(d.val);
            d.dur = Number(d.dur);
            d.acous = Number(d.acous);
            d.spch = Number(d.spch);
            d.pop = Number(d.pop);
        });

        function R(a, b, year){
            //算相關係數
            var i=0, mean_a=0, mean_b=0;
            data.forEach(d => {
                var label = [d.year, d.bpm, d.nrgy, d.dnce, d.dB, d.live, d.val, d.dur, d.acous, d.spch, d.pop];
                if(year<2010 || year>2019 || year==d.year){
                    i++;
                    mean_a += label[a];
                    mean_b += label[b];
                }
            });
            mean_a /= i;
            mean_b /= i;

            var ab=0, a2=0, b2=0;
            data.forEach(d => {
                var label = [d.year, d.bpm, d.nrgy, d.dnce, d.dB, d.live, d.val, d.dur, d.acous, d.spch, d.pop];
                if(year<2010 || year>2019 || year==d.year){
                    ab += (label[a]-mean_a)*(label[b]-mean_b);
                    a2 += (label[a]-mean_a)*(label[a]-mean_a);
                    b2 += (label[b]-mean_b)*(label[b]-mean_b);
                }
            });

            var ans;
            if((Math.sqrt(a2)*Math.sqrt(b2))==0){
                ans = 0
            }else{
                ans = ab/(Math.sqrt(a2)*Math.sqrt(b2));
            }
            //console.log(ans);
            return ans;
        }

        function show_colorbar(color_scale, x, y, h, w){
            //畫 colorbar
            var color_bar = d3.select("#R_graph").append("g").attr("id", "color_bar")
                            .attr("transform", `translate(${RTotalWidth-40}, ${RMargin.top})`);
            var i;
            for(i=0;i<h;i++){
                color_bar.append("rect")
                        .attr("x", x)
                        .attr("y", y+i)
                        .attr("width", w)
                        .attr("height", 2)
                        .attr("fill", color_scale(-(i/h*2-1)));
            }
        }

        var i, j;
        var dxy=Math.min(RWidth, RHeight)/11;

        var svg = d3.select("svg");
        var R_graph = svg.append("g").attr("id", "R_graph").attr("transform", `translate(${RLeft}, ${RTop})`);
        var R_Margin = R_graph.append("g").attr("id", "R_margin").attr("transform", `translate(${RMargin.left}, ${RMargin.top})`);
        var color_scale = d3.scaleSequential().domain([-1, 1]).interpolator(d3.interpolateRdBu);
        var color_val = d3.scaleLinear().domain([1, -1]).range([0, dxy*11]);
        var color_axis = d3.axisRight(color_val);
        
        show_colorbar(color_scale, 0, 0, dxy*11, 15);
        R_graph.append("g").attr("transform", `translate(${RTotalWidth-25}, ${RMargin.top})`).call(color_axis);

        var barChartG = svg.append('g')
                    .attr('id', 'bar-chart');
        var tip = d3.tip().attr("class", "d3-tip").html(d=>Math.round(d.val*1000)/1000);
        barChartG.call(tip);

        for(i=0;i<11;i++){
            for(j=0;j<11;j++){
                var ans = R(i, j, year)
                R_Margin.append("circle")
                        .data([{"val": ans}])
                        .attr("id", "c"+String(i)+"_"+String(j))
                        .attr("cx", j*dxy+dxy/2)
                        .attr("cy", i*dxy+dxy/2)
                        .attr("r", dxy/3*Math.abs(ans)+4)
                        .attr("fill", color_scale(ans))
                        .on("mouseover", tip.show)
                        .on("mouseout", tip.hide);
            }
        }

        for(i=0;i<12;i++){
            R_Margin.append("line").attr("x1", 0).attr("y1", dxy*i).attr("x2", dxy*11).attr("y2", dxy*i).style('stroke', 'gray').style('stroke-width', 2);
            R_Margin.append("line").attr("x1", dxy*i).attr("y1", 0).attr("x2", dxy*i).attr("y2", dxy*11).style('stroke', 'gray').style('stroke-width', 2);
        }

        var label = ["Year", "BPM", "Energy", "Danceability", "Loudness", "Liveness", "Valence", "Length", "Acousticness", "Speechiness", "Popularity"];
        for(i=0;i<11;i++){
            R_graph.append("text").attr("x", RMargin.left+i*dxy).attr("y", 10).attr("transform", `rotate(-30, ${RMargin.left+i*dxy}, 10)`).text(label[i]);
            R_graph.append("text").attr("x", 0).attr("y", RMargin.top+i*dxy+dxy+2).attr("transform", `rotate(-30, 0, ${RMargin.top+i*dxy+dxy/2})`).text(label[i]);
        }
    });
};

function draw_relation_graph(year){
    let RLeft = 800, RTop = 100;
    let RTotalWidth = 560, RTotalHeight = 500;
    let RMargin = {top: 20, right: 45, bottom: 10, left: 85},
        RWidth = RTotalWidth - RMargin.left - RMargin.right, 
        RHeight = RTotalHeight - RMargin.top - RMargin.bottom;


    d3.csv("./Spotify 2010 - 2019 Top 100(new).csv").then(data =>{
        data.forEach(d => {
            d.year = Number(d.top_year);
            d.bpm = Number(d.bpm);
            d.nrgy = Number(d.nrgy);
            d.dnce = Number(d.dnce);
            d.dB = Number(d.dB);
            d.live = Number(d.live);
            d.val = Number(d.val);
            d.dur = Number(d.dur);
            d.acous = Number(d.acous);
            d.spch = Number(d.spch);
            d.pop = Number(d.pop);
        });

        function R(a, b, year){
            //算相關係數
            var i=0, mean_a=0, mean_b=0;
            data.forEach(d => {
                var label = [d.year, d.bpm, d.nrgy, d.dnce, d.dB, d.live, d.val, d.dur, d.acous, d.spch, d.pop];
                if(year<2010 || year>2019 || year==d.year){
                    i++;
                    mean_a += label[a];
                    mean_b += label[b];
                }
            });
            mean_a /= i;
            mean_b /= i;

            var ab=0, a2=0, b2=0;
            data.forEach(d => {
                var label = [d.year, d.bpm, d.nrgy, d.dnce, d.dB, d.live, d.val, d.dur, d.acous, d.spch, d.pop];
                if(year<2010 || year>2019 || year==d.year){
                    ab += (label[a]-mean_a)*(label[b]-mean_b);
                    a2 += (label[a]-mean_a)*(label[a]-mean_a);
                    b2 += (label[b]-mean_b)*(label[b]-mean_b);
                }
            });

            var ans;
            if((Math.sqrt(a2)*Math.sqrt(b2))==0){
                ans = 0
            }else{
                ans = ab/(Math.sqrt(a2)*Math.sqrt(b2));
            }
            //console.log(ans);
            return ans;
        }

        function show_colorbar(color_scale, x, y, h, w){
            //畫 colorbar
            var color_bar = d3.select("#R_graph").append("g").attr("id", "color_bar")
                            .attr("transform", `translate(${RTotalWidth-40}, ${RMargin.top})`);
            var i;
            for(i=0;i<h;i++){
                color_bar.append("rect")
                        .attr("x", x)
                        .attr("y", y+i)
                        .attr("width", w)
                        .attr("height", 2)
                        .attr("fill", color_scale(-(i/h*2-1)));
            }
        }

        var i, j;
        var dxy=Math.min(RWidth, RHeight)/11;

        var svg = d3.select("svg");
        var color_scale = d3.scaleSequential().domain([-1, 1]).interpolator(d3.interpolateRdBu);
        
        show_colorbar(color_scale, 0, 0, dxy*11, 15);

        r_margin = svg.select("#R_graph").select("#R_margin");
        for(i=0;i<11;i++){
            for(j=0;j<11;j++){
                var ans = R(i, j, year)
                r_margin.select("#c"+String(i)+"_"+String(j)).data([{"val": ans}]);
                r_margin.select("#c"+String(i)+"_"+String(j)).transition()
                        .duration(2000)
                        .attr("r", dxy/3*Math.abs(ans)+4)
                        .attr("fill", color_scale(ans));
            }
        }
    });
};